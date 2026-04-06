#include "QtGui.h"
#include "QtDebug"
#include "QMessageBox"
#include "QFileDialog"

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
	img_sink(new ImgSink(this))
{
    ui.setupUi(this);

	connect(ui.hostIpConnectBtn, SIGNAL(clicked()), this, SLOT(on_connect_btn_clicked()));
	connect(ui.deviceSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(on_device_select_changed(int)));
	connect(ui.deviceInfoUpdateBtn, SIGNAL(clicked()), this, SLOT(on_device_info_update_btn_clicked()));

	connect(ui.acquisitionModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_acquisition_mode_changed(int)));
	connect(ui.mechanicalModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_mechanical_mode_changed(int)));
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
	//int num_devices = this->xsystem->FindDevice();
	int num_devices = 1;
	if (num_devices <= 0) {
		QMessageBox::warning(this, "Aviso", "Nenhum dispositivo encontrado.");
		return;
	}

	// Set default values
	ui.integrationTimeInput->setText("10000000");
	ui.filePrefixInput->setText("");

	ui.hostIpInput->setDisabled(true);
	ui.hostIpConnectBtn->setDisabled(true);

	// Enable device info
	ui.deviceSelect->setDisabled(false);
	ui.deviceIpInput->setDisabled(false);

	ui.deviceCmdPortInput->setDisabled(false);
	ui.deviceImgPortInput->setDisabled(false);
	ui.deviceInfoUpdateBtn->setDisabled(false);

	// Enabling operation inputs
	ui.acquisitionModeInput->setDisabled(false);
	ui.mechanicalModeInput->setDisabled(false);
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
	ui.stopGrabBtn->setDisabled(false);
	
	for (int i = 0; i < num_devices; i++) {
		ui.deviceSelect->addItem("Dispositivo " + QString::number(i + 1));
	}

	QMessageBox::information(this, "Status", "Conectado com sucesso ao host " + host_ip + ".");
}

void QtGui::on_device_select_changed(int index) {
	QString selected_option = ui.deviceSelect->itemText(index);
	int device_id = selected_option.split(" ")[1].toInt() - 1;

	if (this->xdevice_ptr != nullptr) {
		this->xacquisition.Close();
		this->xcommand.Close();
		delete this->xdevice_ptr;
	}

	//this->xdevice_ptr = this->xsystem->GetDevice(device_id);
	this->xdevice_ptr = new XDevice(this->xsystem);
	this->xdevice_ptr->SetIP("192.168.1.2");
	this->xdevice_ptr->SetCmdPort(3000);
	this->xdevice_ptr->SetImgPort(4001);
	this->xdevice_ptr->SetDeviceType("1412_KOSTI");
	this->xdevice_ptr->SetSerialNum("1234567890", 10);
	this->xdevice_ptr->SetMAC((uint8_t*)"123456");
	this->xdevice_ptr->SetFirmBuildVer(123);
	this->xdevice_ptr->SetFirmVer(123);

	// Open acquisition connection
	if (this->xcommand.Open(this->xdevice_ptr)) {
		//QMessageBox::information(this, "Status", "Canal de comando aberto com sucesso.");
		if (!this->xacquisition.Open(this->xdevice_ptr, &this->xcommand)) {
			QMessageBox::critical(this, "Erro", "Falha ao abrir o canal de aquisi��o.");
		}
		else {
			//QMessageBox::information(this, "Status", "Canal de imagem aberto com sucesso.");
		}
	}
	else {
		QMessageBox::critical(this, "Erro", "Falha ao abrir o canal de comando.");
	}

	//QString mac_address(reinterpret_cast<char*>(this->xdevice_ptr->GetMAC()));
	//QString firm_ver(reinterpret_cast<char*>(this->xdevice_ptr->GetFirmVer()));
	QString cmd_port = QString::number(this->xdevice_ptr->GetCmdPort());
	QString img_port = QString::number(this->xdevice_ptr->GetImgPort());

	ui.deviceIpInput->setText(this->xdevice_ptr->GetIP());
	//ui.deviceTypeInput->setText(this->xdevice_ptr->GetDeviceType());
	ui.deviceTypeInput->setText("1412_KOSTI");
	//ui.deviceMacInput->setText(mac_address);
	ui.deviceMacInput->setText("");
	//ui.deviceFirmwareInput->setText(firm_ver);
	ui.deviceCmdPortInput->setText(cmd_port);
	ui.deviceImgPortInput->setText(img_port);
	//ui.deviceSerialInput->setText(this->xdevice_ptr->GetSerialNum());
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
		ui.integrationTimeInput->setText("10000000");
		QMessageBox::warning(this, "Aviso", "O tempo de integra\u00E7\u00E3o deve ser positivo n\u00E3o nulo.");
		return;
	}

	if (this->xcommand.SetPara(XPARA_FRAME_PERIOD, integration_time) != 1)
	{
		QMessageBox::critical(this, "Erro", "Falha ao definir o tempo de integra\u00E7\u00E3o.");
	}

	set_total_approximate_time();

}

void QtGui::on_interval_time_changed() {
	int interval_time = ui.intervalTimeInput->text().toInt();

	if (interval_time < 0) {
		ui.integrationTimeInput->setText("1500");
		QMessageBox::warning(this, "Aviso", "O tempo de intervalo deve ser positivo.");
		return;
	}

	set_total_approximate_time();
}

void QtGui::on_image_quantity_combobox_changed(int index) {
	QString selected_image_quantity = ui.imageQuantityComboBox->itemText(index);
	int image_quantity = selected_image_quantity.toInt();

	set_total_approximate_time();
}

void QtGui::on_image_quantity_input_changed() {
	int image_quantity = ui.integrationTimeInput->text().toInt();

	if (image_quantity < 1) {
		ui.imageQuantityInput->setText("5");
		QMessageBox::warning(this, "Aviso", "A quantidade de imagens deve ser positivo n\u00E3o nulo.");
		return;
	}

	set_total_approximate_time();
}

void QtGui::on_file_prefix_input_changed() {
	QString file_prefix= ui.filePrefixInput->text();

	if (file_prefix.toStdString() == "") {
		ui.imageQuantityInput->setText("img");
		QMessageBox::warning(this, "Aviso", "O prefixo n\u00E3o pode ser vazio.");
		return;
	}
}

void QtGui::on_choose_file_path_btn_clicked() {
	this->file_name = QFileDialog::getSaveFileName(this, "Save file", "../images", "DAT files (*.dat);;All files (*.*)");
	ui.filePathInput->setText(this->file_name);
}

void QtGui::on_grab_btn_clicked() {
	
	string file_prefix = ui.filePrefixInput->text().toStdString();
	string file_path = ui.filePathInput->text().toStdString();
	int total_approximate_time = get_total_approximate_time();

	if (file_prefix == "" || file_path == "" || total_approximate_time == 0) {
		QMessageBox::warning(this, "Aviso", "Preencha todos os campos antes de iniciar a opera\u00E7\u00E3o.");
		return;
	}
	
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

	QMessageBox::information(this, "Dispositivo pronto", "clique no botão para iniciar a opera\u00E7\u00E3o");

	for (int i = 0; i < image_quantity; i++) {
		update_progress_tab(i, image_quantity, total_approximate_time, file_prefix);

		this->set_is_save(true);
		this->set_frame_count(0);
		this->set_lost_frame_count(0);
		this->set_save_file_name(file_path + "/" + file_prefix + (std::to_string(i)) + ".dat");

		if (!this->ximg_handle.OpenFile(this->save_file_name.c_str()))
		{
			QMessageBox::critical(this, "Connection", "Falha ao abrir o arquivo de imagem.");
			return;
		}
		this->xacquisition.Grab(1);
		this->xevent.Wait();
		this->ximg_handle.CloseFile();
		if (acquisition_mode == "Tomografia") {
			if (mechanical_mode == "Arduino") {
				//enviarComando(hSerial, "1");
				//Sleep(1000);
				//enviarComando(hSerial, std::to_string(angle_variation));
			}
			else {
				//enviarComando(hSerial, "1");
				//Sleep(1000);
				//enviarComando(hSerial, std::to_string(angle_variation));
			}
		}
		Sleep(interval_time);
	}

	update_progress_tab(image_quantity, image_quantity, total_approximate_time, file_prefix);

	QMessageBox::information(this, "Aquisi\u00E7\u00E3o", "Opera\u00E7\u00E3o completa.");
}

void QtGui::on_stop_grab_btn_clicked() {
	this->xacquisition.Stop();
}

void QtGui::update_progress_tab(int index, int total_images, int total_approximate_time, string file_prefix) {
	QString processing_string = QString("Processando: %1%2.dat")
		.arg(QString::fromStdString(file_prefix))
		.arg(index, 1, 10, QChar('0'));
	ui.currentProcessingImageLabel->setText(processing_string);

	int progress_percent = (index * 100) / total_images;
	QString progress_string = QString("Progresso: 1%/2% (3%%)")
		.arg(index, 1, 10, QChar('0'))
		.arg(total_images, 1, 10, QChar('0'))
		.arg(progress_percent, 1, 10, QChar('0'));
	ui.currentProgressLabel->setText(progress_string);

	int integration_time = ui.integrationTimeInput->text().toInt();
	int interval_time = ui.intervalTimeInput->text().toInt();
	int approximate_elapsed_time =
		(index * 1) +
		(index* (integration_time * 1.0 / 1000000)) +
		(index * (interval_time * 1.0 / 1000));
	int remaining_time = total_approximate_time - approximate_elapsed_time;
	int rt_hh = remaining_time/ 3600;
	int rt_mm = (remaining_time % 3600) / 60;
	int rt_ss = remaining_time % 60;

	QString remaining_time_string = QString("Tempo restante: %1:%2:%3")
		.arg(rt_hh, 2, 10, QChar('0'))
		.arg(rt_mm, 2, 10, QChar('0'))
		.arg(rt_ss, 2, 10, QChar('0'));
	ui.remainingTimeLabel->setText(remaining_time_string);

	QString status_string = QString("Status: Em opera\u00E7\u00E3o");

	QString current_displayed_string = QString("Exibindo: %1%2.dat")
		.arg(QString::fromStdString(file_prefix))
		.arg(index - 1, 1, 10, QChar('0'));


	QString elapsed_time_string = QString("Tempo decorrido: ---");

	if (index == 0) {
		current_displayed_string = QString("Exibindo: ---");
	}
	else if (index < total_images) {

	}
	else {
		status_string = QString("Status: Conclu\u00eddo");
		ui.currentProcessingImageLabel->setText("Processando: ---");
		ui.remainingTimeLabel->setText("Tempo restante: ---");
	}
	
	ui.currentStatusLabel->setText(status_string);
	ui.currentDisplayedImageLabel->setText(current_displayed_string);

	update_displayed_image(index-1);
}

void QtGui::update_displayed_image(int index) {
	int width = 1200;
	int height = 1400;
	int total_size = width * height;
	
	QFile file(QString::fromStdString(this->get_save_file_name()));
	file.open(QIODevice::ReadOnly);

	QByteArray data_u16_bits = file.readAll();
	QByteArray data_u8_bits(total_size,0);
	for (int i = 0; i < total_size; i++) {
		data_u8_bits[i] = data_u16_bits[(i * 2) + 1];
	}

	QImage img((uchar*)data_u8_bits.data(),
		width,
		height,
		QImage::Format_Grayscale8);

	ui.imageLabel->setPixmap(QPixmap::fromImage(img));
}

QString QtGui::get_file_name() {
	return this->file_name;
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
	if (acquisition_mode.toStdString() == "Radiografia") {
		image_quantity = ui.imageQuantityComboBox->currentText().toInt();
	}
	else {
		image_quantity = ui.imageQuantityInput->text().toInt();
	}

	if (integration_time == 0 || image_quantity == 0)
		return 0;

	int approximate_total_time = 
			(image_quantity * 1) + 
			(image_quantity * (integration_time*1.0/1000000)) + 
			(image_quantity * (interval_time*1.0/1000));
	
	return approximate_total_time;
}

void QtGui::set_total_approximate_time() {
	int total_time = get_total_approximate_time();
	if (total_time != 0) {
		int hh = total_time / 3600;
		int mm = (total_time % 3600) / 60;
		int ss = total_time % 60;

		QString text = QString("Tempo total esperado: %1:%2:%3")
			.arg(hh, 2, 10, QChar('0'))
			.arg(mm, 2, 10, QChar('0'))
			.arg(ss, 2, 10, QChar('0'));

		ui.totalTimeInput->setText(text);
	}
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
