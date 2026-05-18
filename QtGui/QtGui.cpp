#include "QtGui.h"
#include "QtDebug"
#include "QMessageBox"
#include "QFileDialog"
#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QWaitCondition>

#include "stdafx.h"

#include "xsystem.h"
#include "xdevice.h"
#include "xcommand.h"

#include "xacquisition.h"
#include "xframe_transfer.h"
#include "xgig_factory.h"

#include "CmdSink.h"
#include "ImgSink.h"

#include "ximage_handler.h"
#include "xcorrection.h"

#include "xthread_win.h"

#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <locale>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include "utils.h"

#pragma comment(lib, "..\\lib\\x64\\XLibDllKosti.lib")

using namespace std;

//The allocated buffer size for the grabbed frames
#if defined(_WIN64)
uint32_t frame_buffer_size = 700;
#else
uint32_t frame_buffer_size = 400;
#endif


QtGui::QtGui(QWidget *parent)
    : QMainWindow(parent),
	xsystem(nullptr),
	xdevice_ptr(nullptr),
	xtransfer(),
	xfactory(),
	xcommand(&xfactory),
	xacquisition(&xfactory),
	cmd_sink(new CmdSink(this)),
	img_sink(new ImgSink(this)),
	frame_count(0),
	lost_frame_count(0),
	is_save(false)
{
    ui.setupUi(this);
	
	serial = new QSerialPort(this);

	connect(serial, &QSerialPort::readyRead, this, &QtGui::arduino_serial_read);

	connect(ui.hostIpConnectBtn, SIGNAL(clicked()), this, SLOT(on_connect_btn_clicked()));
	connect(ui.deviceSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(on_device_select_changed(int)));
	connect(ui.deviceInfoUpdateBtn, SIGNAL(clicked()), this, SLOT(on_device_info_update_btn_clicked()));

	connect(ui.acquisitionModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_acquisition_mode_changed(int)));
	connect(ui.mechanicalModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_mechanical_mode_changed(int)));
	connect(ui.mechanicalConnectBtn, SIGNAL(clicked()), this, SLOT(on_mechanical_connect_btn_clicked()));

	connect(ui.binningModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_binning_mode_changed(int)));
	connect(ui.gainModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_gain_mode_changed(int)));

	connect(ui.integrationTimeInput, SIGNAL(editingFinished()), this, SLOT(on_integration_time_changed()));
	connect(ui.intervalTimeInput, SIGNAL(editingFinished()), this, SLOT(on_interval_time_changed()));

	connect(ui.imageQuantityComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_image_quantity_combobox_changed(int)));
	connect(ui.imageQuantityInput, SIGNAL(editingFinished()), this, SLOT(on_image_quantity_input_changed()));
	
	connect(ui.filePrefixInput, SIGNAL(editingFinished()), this, SLOT(on_file_prefix_input_changed()));

	connect(ui.chooseFilePathBtn, SIGNAL(clicked()), this, SLOT(on_choose_file_path_btn_clicked()));
	connect(ui.grabBtn, SIGNAL(clicked()), this, SLOT(on_grab_btn_clicked()));
	connect(ui.stopGrabBtn, SIGNAL(clicked()), this, SLOT(on_stop_grab_btn_clicked()));
}

void QtGui::on_connect_btn_clicked() {
	QString host_ip = ui.hostIpInput->text();
	char host_ip_c[20];

	if (!isValidIP(host_ip.toStdString())) {
		QMessageBox::warning(this, "Aviso", "Endere\u00E7o de IP inv\u00E1lido.");
		return;
	}

	std::strcpy(host_ip_c, host_ip.toStdString().c_str());

	// Create objects
	this->xsystem = new XSystem(host_ip_c);
	this->xsystem->RegisterEventSink(this->cmd_sink);

	this->xcommand.RegisterEventSink(this->cmd_sink);

	this->xtransfer.RegisterEventSink(this->img_sink);

	this->xacquisition.RegisterEventSink(this->img_sink);
	this->xacquisition.RegisterFrameTransfer(&this->xtransfer);

	// Open system connection
	if (!this->xsystem->Open()) {
		QMessageBox::critical(this, "Erro", "Falha ao conectar ao host " + host_ip + ".");
		return;
	}

	// Find device
	int num_devices = this->xsystem->FindDevice();
	if (num_devices <= 0) {
		QMessageBox::warning(this, "Aviso", "Nenhum dispositivo encontrado.");
		return;
	}

	// Disable ip input and enable device selection
	ui.hostIpInput->setDisabled(true);
	ui.hostIpConnectBtn->setDisabled(true);
	ui.deviceSelect->setDisabled(false);
	
	for (int i = 0; i < num_devices; i++) {
		ui.deviceSelect->addItem("Dispositivo " + QString::number(i + 1));
	}

	QMessageBox::information(this, "Status", "Conectado com sucesso ao host " + host_ip + ".");
}

void QtGui::on_device_select_changed(int index) {
	// Checando se o dispositivo selecionado é valido
	QString selected_option = ui.deviceSelect->itemText(index);
	int device_id = selected_option.split(" ")[1].toInt() - 1;

	if (this->xdevice_ptr != nullptr) {
		this->xcommand.Close();
		this->xacquisition.Close();
		//delete this->xdevice_ptr;
		this->xdevice_ptr = nullptr;
	}

	this->xdevice_ptr = this->xsystem->GetDevice(device_id);
	if (!this->xdevice_ptr) {
		QMessageBox::critical(this, "Erro", "Dispositivo inválido.");
		return;
	}

	//Dispositivo generico
	/*this->xdevice_ptr = new XDevice(this->xsystem);
	this->xdevice_ptr->SetIP("192.168.1.2");
	this->xdevice_ptr->SetCmdPort(3000);
	this->xdevice_ptr->SetImgPort(4001);
	this->xdevice_ptr->SetDeviceType("1412_KOSTI");
	this->xdevice_ptr->SetSerialNum("1234567890", 10);
	this->xdevice_ptr->SetMAC((uint8_t*)"123456");
	this->xdevice_ptr->SetFirmBuildVer(123);
	this->xdevice_ptr->SetFirmVer(123);*/


	//O dispositivo selecionado é válido, então vamos estabelecer conexão com as portas
	// Open acquisition connection
	if (this->xcommand.Open(this->xdevice_ptr)) {
		//QMessageBox::information(this, "Status", "Canal de comando aberto com sucesso.");
		if (!this->xacquisition.Open(this->xdevice_ptr, &this->xcommand)) {
			QMessageBox::critical(this, "Erro", "Falha ao abrir o canal de aquisi\u00E7\u00E3o.");
			return;
		}
		else {
			//QMessageBox::information(this, "Status", "Canal de aquisição aberto com sucesso.");
		}
	}
	else {
		QMessageBox::critical(this, "Erro", "Falha ao abrir o canal de comando.");
		return;
	}


	//comunicação estabelecida, agora exibimos os dados do dispositivo nos labels do qt
	
	//uma possível maneira de interpretar o retorno do get mac
	//uint8_t* mac = this->xdevice_ptr->GetMAC();
	//QString mac_address = QString("%1:%2:%3:%4:%5:%6")
	//	.arg(mac[0], 2, 16, QChar('0'))
	//	.arg(mac[1], 2, 16, QChar('0'))
	//	.arg(mac[2], 2, 16, QChar('0'))
	//	.arg(mac[3], 2, 16, QChar('0'))
	//	.arg(mac[4], 2, 16, QChar('0'))
	//	.arg(mac[5], 2, 16, QChar('0'));

	QString firm_ver = QString::number(this->xdevice_ptr->GetFirmVer());
	QString cmd_port = QString::number(this->xdevice_ptr->GetCmdPort());
	QString img_port = QString::number(this->xdevice_ptr->GetImgPort());

	ui.deviceIpInput->setText(this->xdevice_ptr->GetIP());
	ui.deviceTypeInput->setText(this->xdevice_ptr->GetDeviceType());
	//ui.deviceTypeInput->setText("1412_KOSTI");
	//ui.deviceMacInput->setText(mac_address);
	ui.deviceMacInput->setText("");
	ui.deviceFirmwareInput->setText(firm_ver);
	ui.deviceCmdPortInput->setText(cmd_port);
	ui.deviceImgPortInput->setText(img_port);
	ui.deviceSerialInput->setText(this->xdevice_ptr->GetSerialNum());


	//Permitimos a atualização dos dados do dispositivo
	//Enabling device data update
	/*ui.deviceIpInput->setDisabled(false);
	ui.deviceCmdPortInput->setDisabled(false);
	ui.deviceImgPortInput->setDisabled(false);
	ui.deviceInfoUpdateBtn->setDisabled(false);*/

	// e pertmitimos a configuração e operação do dispositivo
	ui.acquisitionModeInput->setDisabled(false);
	ui.mechanicalModeInput->setDisabled(false);
	ui.mechanicalConnectBtn->setDisabled(false);

	ui.binningModeInput->setDisabled(false);
	ui.gainModeInput->setDisabled(false);
	ui.integrationTimeInput->setDisabled(false);
	ui.intervalTimeInput->setDisabled(false);

	ui.imageQuantityStackedWidget->setDisabled(false);
	ui.imageQuantityComboBox->setDisabled(false);
	ui.imageQuantityInput->setDisabled(false);

	ui.filePrefixInput->setDisabled(false);
	ui.filePathInput->setDisabled(false);
	ui.chooseFilePathBtn->setDisabled(false);
	ui.grabBtn->setDisabled(false);
	//ui.stopGrabBtn->setDisabled(false);

	//garantimos que "tomografia" e "imagecombobox" estejam selecionados por padrão
	ui.acquisitionModeInput->setCurrentIndex(0);
	ui.imageQuantityStackedWidget->setCurrentIndex(0);

	//e definimos alguns valores padrões para o dispositivo
	if (this->xcommand.SetPara(XPARA_BINNING_MODE, 0) != 1)
	{
		QMessageBox::critical(this, "Erro", "Falha ao definir o modo de binning");
	}

	if (this->xcommand.SetPara(XPARA_GAIN_RANGE, 1) != 1)
	{
		QMessageBox::critical(this, "Erro", "Falha ao definir o modo de ganho.");
	}

	if (this->xcommand.SetPara(XPARA_FRAME_PERIOD, 1000000) != 1)
	{
		QMessageBox::critical(this, "Erro", "Falha ao definir o tempo de integra\u00E7\u00E3o.");
	}
}

void QtGui::on_device_info_update_btn_clicked() {
	int device_id = ui.deviceSelect->currentIndex() - 1;

	QString ip = ui.deviceIpInput->text();
	QString cmd_port = ui.deviceCmdPortInput->text();
	QString img_port = ui.deviceImgPortInput->text();

	this->xdevice_ptr->SetIP(ip.toStdString().c_str());
	this->xdevice_ptr->SetCmdPort(cmd_port.toInt());
	this->xdevice_ptr->SetImgPort(img_port.toInt());

	if (1 == this->xsystem->ConfigureDevice(xdevice_ptr))
	{
		this->xdevice_ptr = this->xsystem->GetDevice(device_id);
	}
	else
	{
		QMessageBox::critical(this, "Erro", "Falha ao configurar dispositivo.");
		return;
	}
}

void QtGui::on_acquisition_mode_changed(int index) {
	QString selected_acquisition_mode = ui.acquisitionModeInput->itemText(index);

	if (selected_acquisition_mode == "Tomografia") {
		ui.imageQuantityStackedWidget->setCurrentIndex(0);
	}
	else {
		ui.imageQuantityStackedWidget->setCurrentIndex(1);
	}

	set_total_approximate_time();

	return;
}

void QtGui::on_mechanical_mode_changed(int index) {
	QString selected_mechanical_mode = ui.mechanicalModeInput->itemText(index);

	if (selected_mechanical_mode == QString("Arduino")) {

	}
	else {

	}

	return;
}

void QtGui::on_mechanical_connect_btn_clicked() {
	arduino_connect_serial_port();
}

void QtGui::arduino_connect_serial_port() {
	if (serial->isOpen())
		serial->close();

	serial->setPortName("COM4");
	serial->setBaudRate(QSerialPort::Baud9600);
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	serial->setFlowControl(QSerialPort::NoFlowControl);

	if (!serial->open(QIODevice::ReadWrite )) {//| QIODevice::Unbuffered)
		QMessageBox::critical(this, "Erro:", "N\u00E3o foi possível abrir a porta serial:\n" + serial->errorString());
	}
	else {
		QMessageBox::information(this, "Status:", "Conex\u00E3o estabelecida com o arduino.");
	}
}

void QtGui::on_binning_mode_changed(int index) {
	QString selected_binning_mode = ui.binningModeInput->itemText(index);
	int binning_mode = selected_binning_mode.toStdString() == "Normal" ? 0: 1;

	if (1 != this->xcommand.SetPara(XPARA_BINNING_MODE, binning_mode))
	{
		QMessageBox::critical(this, "Connection", "Falha ao definir o modo de binning");
	}
}

void QtGui::on_gain_mode_changed(int index) {
	QString selected_gain_mode = ui.gainModeInput->itemText(index);
	int gain_mode = selected_gain_mode.toStdString() == "Alto" ? 256 : 1;

	if (this->xcommand.SetPara(XPARA_GAIN_RANGE, gain_mode) != 1)
	{
		QMessageBox::critical(this, "Erro", "Falha ao definir o modo de ganho.");
	}
}

void QtGui::on_integration_time_changed() {
	int integration_time = ui.integrationTimeInput->text().toInt();

	if (integration_time < 1) {
		QMessageBox::warning(this, "Aviso", "O tempo de integra\u00E7\u00E3o deve ser maior que 0s.");
		ui.integrationTimeInput->setText("1000000");
		integration_time = 1000000;
	}

	if (this->xcommand.SetPara(XPARA_FRAME_PERIOD, integration_time) != 1)
	{
		QMessageBox::critical(this, "Erro", "Falha ao definir o tempo de integra\u00E7\u00E3o.");
		ui.integrationTimeInput->setText("");
		integration_time = 0;
	}

	set_total_approximate_time();
}

void QtGui::on_interval_time_changed() {
	int interval_time = ui.intervalTimeInput->text().toInt();

	if (interval_time < 0) {
		QMessageBox::warning(this, "Aviso", "O tempo de intervalo deve ser maior que ou igual a 0s.");
		ui.integrationTimeInput->setText("1500");
	}

	set_total_approximate_time();
}

void QtGui::on_image_quantity_combobox_changed(int index) {
	QString selected_image_quantity = ui.imageQuantityComboBox->itemText(index);
	int image_quantity = selected_image_quantity.toInt();

	set_total_approximate_time();
}

void QtGui::on_image_quantity_input_changed() {
	int image_quantity = ui.imageQuantityInput->text().toInt();

	if (image_quantity < 1) {
		QMessageBox::warning(this, "Aviso", "A quantidade de imagens deve maior que 0.");
		ui.imageQuantityInput->setText("5");
	}

	set_total_approximate_time();
}

void QtGui::on_file_prefix_input_changed() {
	QString file_prefix= ui.filePrefixInput->text();

	if (file_prefix.toStdString() == "") {
		QMessageBox::warning(this, "Aviso", "O prefixo n\u00E3o pode ser vazio.");
		ui.filePrefixInput->setText("img");
		return;
	}
}

void QtGui::on_choose_file_path_btn_clicked() {
	this->path_name = QFileDialog::getExistingDirectory(this, "Escolha um diretório", "C:/");
	ui.filePathInput->setText(this->path_name);
}

void QtGui::on_grab_btn_clicked() {
	
	string file_prefix = ui.filePrefixInput->text().toStdString();
	string file_path = ui.filePathInput->text().toStdString();
	int total_approximate_time = get_total_approximate_time();

	if (file_prefix == "" || file_path == "" || total_approximate_time <= 0) {
		QMessageBox::warning(this, "Aviso", "Preencha todos os campos antes de iniciar a opera\u00E7\u00E3o.");
		return;
	}
	
	//precisa checar também os parametros direto pelo dispositivo:
	string acquisition_mode = ui.acquisitionModeInput->currentText().toStdString();
	string mechanical_mode = ui.mechanicalModeInput->currentText().toStdString();
	int interval_time = ui.intervalTimeInput->text().toInt();
	int image_quantity = 0;
	if (acquisition_mode == "Tomografia") {
		image_quantity = ui.imageQuantityComboBox->currentText().toInt();
	}
	else {
		image_quantity = ui.imageQuantityInput->text().toInt();
	}

	QMessageBox::information(this, "Dispositivo pronto", "clique no bot\u00E3o para iniciar a opera\u00E7\u00E3o");
	//desabilitando todos os inputs exceto o parar. 
	//Sempre que o grab parar seja lá qual o motivo, a função para habilitar os inputs deve ser chamada
	on_operation_start_disable_all();
	this->stop_bnt_pressed == false;
	time_t starting_time = time(nullptr);

	logWriteStart();
	for (int i = 0; i < image_quantity && this->stop_bnt_pressed == false; i++) {
		sync.lock();
		update_progress_tab(i, image_quantity, starting_time, file_prefix);
		
		QString inicioCicloX =
			QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]") + 
			" - Iniciando ciclo " + QString::number(i + 1) + "\n";
		escreverMensagem("log.txt", inicioCicloX);

		this->set_is_save(true);
		this->set_frame_count(0);
		this->set_lost_frame_count(0);
		this->set_save_file_name(file_path + "/" + file_prefix + (std::to_string(i+1)) + ".dat");

		if (!this->ximg_handle.OpenFile(this->save_file_name.c_str()))
		{
			QMessageBox::critical(this, "Connection", "Falha ao abrir o arquivo de imagem.");
			on_operation_end_enable_all();
			return;
		}

		QString grabXStart =
			QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]") + 
			" - Capturando " + QString::fromStdString(file_prefix) + QString::number(i + 1) + ".dat" + "\n";
		escreverMensagem("log.txt", grabXStart);

		this->xacquisition.Grab(1);
		this->xevent.Wait();
		this->ximg_handle.CloseFile();

		QString grabXFinish =
			QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]") +
			" - " + QString::fromStdString(file_prefix) + QString::number(i + 1) + ".dat capturado" + "\n";
		escreverMensagem("log.txt", grabXFinish);


		if (acquisition_mode == "Tomografia") {
			arduino_send_command("1");
			Sleep(1000);
			float angle = 360.0f / (ui.imageQuantityComboBox->currentText().toFloat());
			arduino_send_command(std::to_string(angle));
		}
		sync.unlock();
		QString fimCicloX =
			QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]") +
			" - Finalizando ciclo " + QString::number(i + 1) + "\n";
		escreverMensagem("log.txt", fimCicloX);
		Sleep(interval_time);
	}

	QString fimOperacao =
		QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]") +
		" - Finalizando operacao" + "\n";
	escreverMensagem("log.txt", fimOperacao);

	update_progress_tab(image_quantity, image_quantity, starting_time, file_prefix);
	QMessageBox::information(this, "Aquisi\u00E7\u00E3o", "Opera\u00E7\u00E3o completa.");
	on_operation_end_enable_all();
}

void QtGui::arduino_send_command(const std::string& comando) {

	if (!serial->isOpen()) {
		QMessageBox::critical(this, "porta serial:", "porta serial nao esta aberta");
		return;
	}
	serial->write((comando + "\n").c_str());
	serial->waitForBytesWritten(1000);
	serial->flush();

	QString arduinoComando =
		QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]") +
		" - Enviando comando '" + QString::fromStdString(comando) + "' ao arduino " + "\n";
	escreverMensagem("log.txt", arduinoComando);
}

void QtGui::arduino_serial_read() {
	buffer.append(serial->readAll());

	while (buffer.contains('\n')) {
		int index = buffer.indexOf('\n');
		QByteArray linha = buffer.left(index);
		buffer.remove(0, index + 1);

		QString mensagem = QString::fromUtf8(linha);
		qDebug() << "Recebido:" << mensagem;
	}
}

void QtGui::on_operation_start_disable_all() {
	ui.deviceSelect->setDisabled(true);

	ui.acquisitionModeInput->setDisabled(true);
	ui.mechanicalModeInput->setDisabled(true);
	ui.mechanicalConnectBtn->setDisabled(true);

	ui.binningModeInput->setDisabled(true);
	ui.gainModeInput->setDisabled(true);
	ui.integrationTimeInput->setDisabled(true);
	ui.intervalTimeInput->setDisabled(true);

	ui.imageQuantityComboBox->setDisabled(true);
	ui.imageQuantityInput->setDisabled(true);

	ui.filePrefixInput->setDisabled(true);
	ui.filePathInput->setDisabled(true);
	ui.chooseFilePathBtn->setDisabled(true);
	ui.grabBtn->setDisabled(true);

	ui.stopGrabBtn->setDisabled(false);
}

void QtGui::on_operation_end_enable_all() {
	ui.deviceSelect->setDisabled(false);

	ui.acquisitionModeInput->setDisabled(false);
	ui.mechanicalModeInput->setDisabled(false);
	ui.mechanicalConnectBtn->setDisabled(false);

	ui.binningModeInput->setDisabled(false);
	ui.gainModeInput->setDisabled(false);
	ui.integrationTimeInput->setDisabled(false);
	ui.intervalTimeInput->setDisabled(false);

	ui.imageQuantityComboBox->setDisabled(false);
	ui.imageQuantityInput->setDisabled(false);

	ui.filePrefixInput->setDisabled(false);
	ui.filePathInput->setDisabled(false);
	ui.chooseFilePathBtn->setDisabled(false);
	ui.grabBtn->setDisabled(false);

	ui.stopGrabBtn->setDisabled(true);
}

void QtGui::on_stop_grab_btn_clicked() {
	this->stop_bnt_pressed = true;
	this->xacquisition.Stop();
	on_operation_end_enable_all();
}

void QtGui::update_progress_tab(int index, int total_images, time_t starting_time, string file_prefix) {
	
	//EXIBINDO
	QString current_displayed_string = QString("Exibindo: %1%2.dat")
		.arg(QString::fromStdString(file_prefix))
		.arg(index, 1, 10, QChar('0'));
	if (index == 0) {
		current_displayed_string = QString("Exibindo: ---");
	}
	ui.currentDisplayedImageLabel->setText(current_displayed_string);

	//PROCESSANDO
	QString processing_string = QString("Processando: %1%2.dat")
		.arg(QString::fromStdString(file_prefix))
		.arg(index+1, 1, 10, QChar('0'));
	if (index == total_images) {
		processing_string = QString("Processando: ---");
	}
	ui.currentProcessingImageLabel->setText(processing_string);

	//PROGRESSO
	int progress_percent = (index * 100) / total_images;
	QString progress_string = QString("Progresso: %1/%2 (%3%)")
		.arg(index, 1, 10, QChar('0'))
		.arg(total_images, 1, 10, QChar('0'))
		.arg(progress_percent, 1, 10, QChar('0'));
	ui.currentProgressLabel->setText(progress_string);

	//ELAPSED TIME
	time_t elapsed_time_t = time(nullptr) - starting_time;
	int el_hh = elapsed_time_t / 3600;
	int el_mm = (elapsed_time_t % 3600) / 60;
	int el_ss = elapsed_time_t % 60;
	QString elapsed_time_string = QString("Tempo decorrido: %1:%2:%3")
		.arg(el_hh, 3, 10, QChar('0'))
		.arg(el_mm, 2, 10, QChar('0'))
		.arg(el_ss, 2, 10, QChar('0'));
	ui.elapsedTimeLabel->setText(elapsed_time_string);

	//REMAINING TIME
	int integration_time = ui.integrationTimeInput->text().toInt();
	int interval_time = ui.intervalTimeInput->text().toInt();
	int approximate_remaining_time = (total_images - index) *
		(1 + (integration_time * 1.0) / 1000000 + (interval_time * 1.0) / 1000);
	int rt_hh = approximate_remaining_time / 3600;
	int rt_mm = (approximate_remaining_time % 3600) / 60;
	int rt_ss = approximate_remaining_time % 60;
	QString remaining_time_string = QString("Tempo restante: %1:%2:%3")
		.arg(rt_hh, 3, 10, QChar('0'))
		.arg(rt_mm, 2, 10, QChar('0'))
		.arg(rt_ss, 2, 10, QChar('0'));
	ui.remainingTimeLabel->setText(remaining_time_string);

	//STATUS
	QString status_string = QString("Status: Em opera\u00E7\u00E3o");
	if (index == total_images) {
		status_string = QString("Status: Conclu\u00eddo");
	}
	ui.currentStatusLabel->setText(status_string);

	//PROGRESS BAR
	ui.progressBar->setMaximum(total_images);
	ui.progressBar->setValue(index);
	if (index == 0) {
		ui.progressBar->setRange(0, total_images);
	}

	//IMAGE
	if (index != 0) {
		update_displayed_image();
	}

	//STOP BUTTON
	if(this->stop_bnt_pressed == true)
		status_string = QString("Status: Parado");
}

void QtGui::update_displayed_image() {
	int width = 1400;
	int height = 1200;
	int total_size = width * height;
	
	QFile file(QString::fromStdString(this->get_save_file_name()));
	file.open(QIODevice::ReadOnly);

	QByteArray data_u16_bits = file.readAll();
	QByteArray data_u8_bits(total_size, 0);

	unsigned short int b16_value = 0;
	unsigned char b8_value = 0;

	//encontrando o intervalo para normalizacao
	uint16_t min_val = 65535;
	uint16_t max_val = 0;

	for (int i = 0; i < total_size; i++) {
		uint16_t val =
			(unsigned char)data_u16_bits[i * 2] |
			((unsigned char)data_u16_bits[i * 2 + 1] << 8);

		if (val < min_val) min_val = val;
		if (val > max_val) max_val = val;
	}

	for (int i = 0; i < total_size; i++) {
		uint16_t val =
			(unsigned char)data_u16_bits[i * 2] |
			((unsigned char)data_u16_bits[i * 2 + 1] << 8);

		unsigned char normalized = 0;

		if (max_val > min_val) {
			normalized = (val - min_val) * 255 / (max_val - min_val);
		}

		data_u8_bits[i] = normalized;
	}

	QImage img((uchar*)data_u8_bits.data(),
		width,
		height,
		QImage::Format_Grayscale8);

	ui.imageLabel->setPixmap(
		QPixmap::fromImage(img).scaled(
			420,
			360,
			Qt::KeepAspectRatio,
			Qt::SmoothTransformation
		)
	);

	file.close();
}



QString QtGui::get_path_name() {
	return this->path_name;
}

uint32_t QtGui::get_frame_count() {
	return this->frame_count;
}

uint32_t QtGui::get_lost_frame_count() {
	return this->lost_frame_count;
}

bool QtGui::get_is_save() {
	return this->is_save;
}

std::string QtGui::get_save_file_name() {
	return this->save_file_name;
}

XImageHandler* QtGui::get_ximage_handler() {
	return &ximg_handle;
}

XEvent* QtGui::get_xevent()
{
	return &this->xevent;
}

int QtGui::get_total_approximate_time() {
	int integration_time = ui.integrationTimeInput->text().toInt();
	int interval_time = ui.intervalTimeInput->text().toInt();
	
	int image_quantity = 0;

	QString acquisition_mode = ui.acquisitionModeInput->currentText();

	if (acquisition_mode.toStdString() == "Tomografia") {
		image_quantity = ui.imageQuantityComboBox->currentText().toInt();
	}
	else {
		image_quantity = ui.imageQuantityInput->text().toInt();
	}

	if (integration_time == 0 || image_quantity == 0)
		return 0;

	int approximate_total_time = image_quantity * 
		(1 + (integration_time * 1.0)/1000000 + (interval_time * 1.0)/1000);

	return approximate_total_time;
}

void QtGui::set_total_approximate_time() {
	int total_time = get_total_approximate_time();
	if (total_time != 0) {
		int hh = total_time / 3600;
		int mm = (total_time % 3600) / 60;
		int ss = total_time % 60;

		QString text = QString("%1:%2:%3")
			.arg(hh, 3, 10, QChar('0'))
			.arg(mm, 2, 10, QChar('0'))
			.arg(ss, 2, 10, QChar('0'));

		ui.totalTimeInput->setText(text);
	}
}

void QtGui::escreverMensagem(const QString& caminhoArquivo, const QString& mensagem)
{
	QFile arquivo(caminhoArquivo);

	// Abre o arquivo em modo Append (adiciona no final)
	if (arquivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
	{
		QTextStream out(&arquivo);
		out << mensagem << "\n";

		arquivo.close();
	}
	else
	{
		qDebug() << "Erro ao abrir arquivo!";
	}
}

void QtGui::logWriteStart(){
	QString acquisition_mode = ui.acquisitionModeInput->currentText();

	QString mechanical_mode = ui.mechanicalModeInput->currentText();

	uint64_t binning;
	if (this->xcommand.GetPara(XPARA_BINNING_MODE, binning) != 1)
	{
	}
	QString binningQS = (binning == 0 ? "Normal" : "2x2");

	uint64_t gain;
	if (this->xcommand.GetPara(XPARA_GAIN_RANGE, gain) != 1)
	{
	}
	QString gainQS = (gain == 0 ? "Low" : "High");

	uint64_t integration;
	if (this->xcommand.GetPara(XPARA_FRAME_PERIOD, integration) != 1)
	{
	}
	QString integrationQs = QString::number(integration);

	QString interval_time = ui.intervalTimeInput->text();

	QString image_quantity = 0;
	if (acquisition_mode == "Tomografia") {
		image_quantity = ui.imageQuantityComboBox->currentText();
	}
	else {
		image_quantity = ui.imageQuantityInput->text();
	}

	QString prefix = ui.filePrefixInput->text();
	QString path = ui.filePathInput->text();

	QString logText =
		"Aquisicao: " + acquisition_mode + "\n" +
		"Mecanismo: " + mechanical_mode + "\n" +
		"Binning: " + binningQS + "\n" +
		"Ganho: " + gainQS + "\n" +
		"Integracao: " + integrationQs + "\n" +
		"Intervalo: " + interval_time + "\n" +
		"Imagens: " + image_quantity + "\n" +
		"Prefixo: " + prefix + "\n" +
		"Diretorio: " + path + "\n" +
		"Iniciando as: " +
		QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]");

	QString logPath = path + "log.txt";
	escreverMensagem(logPath, logText);
}

void QtGui::set_frame_count(uint32_t frame_count) {
	this->frame_count = frame_count;
}

void QtGui::set_lost_frame_count(uint32_t lost_frame_count) {
	this->lost_frame_count = lost_frame_count;
}

void QtGui::set_is_save(bool is_save) {
	this->is_save = is_save;
}

void QtGui::set_save_file_name(std::string save_file_name) {
	this->save_file_name = save_file_name;
}

QtGui::~QtGui()
{}
