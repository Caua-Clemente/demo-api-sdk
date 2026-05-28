#include "QtGui.h"
#include "QtDebug"
#include "QMessageBox"
#include "QFileDialog"
#include <QFile>
#include <QTextStream>
#include <QThread>

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <locale>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include "utils.h"

#include "DetectorWorker.h"

using namespace std;

//The allocated buffer size for the grabbed frames
#if defined(_WIN64)
uint32_t frame_buffer_size = 700;
#else
uint32_t frame_buffer_size = 400;
#endif


QtGui::QtGui(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	
	workerThread = new QThread(this);
	worker = new DetectorWorker();
	worker->moveToThread(workerThread);

	//OK
	connect(ui.hostIpConnectBtn, SIGNAL(clicked()), this, SLOT(on_connect_btn_clicked()));
	connect(worker, &DetectorWorker::device_conection_success, this, &QtGui::on_device_connect_signal);

	//OK
	connect(ui.deviceSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(on_device_select_changed(int)));
	connect(worker, &DetectorWorker::device_select_success, this, &QtGui::on_device_select_success_signal);

	//TODO FUTURE
	connect(ui.deviceInfoUpdateBtn, SIGNAL(clicked()), this, SLOT(on_device_info_update_btn_clicked()));

	//TODO
	connect(ui.acquisitionModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_acquisition_mode_changed(int)));
	connect(ui.mechanicalModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_mechanical_mode_changed(int)));
	connect(ui.mechanicalConnectBtn, SIGNAL(clicked()), this, SLOT(on_mechanical_connect_btn_clicked()));

	//OK
	connect(ui.binningModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_binning_mode_changed(int)));
	connect(ui.gainModeInput, SIGNAL(currentIndexChanged(int)), this, SLOT(on_gain_mode_changed(int)));
	connect(ui.integrationTimeInput, SIGNAL(editingFinished()), this, SLOT(on_integration_time_changed()));
	connect(worker, &DetectorWorker::integration_time_change_end, this, &QtGui::on_integration_time_signal);
	connect(ui.intervalTimeInput, SIGNAL(editingFinished()), this, SLOT(on_interval_time_changed()));

	connect(ui.imageQuantityComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_image_quantity_combobox_changed(int)));
	connect(ui.imageQuantityInput, SIGNAL(editingFinished()), this, SLOT(on_image_quantity_input_changed()));
	
	connect(ui.filePrefixInput, SIGNAL(editingFinished()), this, SLOT(on_file_prefix_input_changed()));
	connect(ui.chooseFilePathBtn, SIGNAL(clicked()), this, SLOT(on_choose_file_path_btn_clicked()));
	connect(ui.grabBtn, SIGNAL(clicked()), this, SLOT(on_grab_btn_clicked()));
	connect(ui.stopGrabBtn, SIGNAL(clicked()), this, SLOT(on_stop_grab_btn_clicked()));

	connect(worker, &DetectorWorker::enable_all, this, &QtGui::on_operation_end_enable_all);
	connect(worker, &DetectorWorker::disable_all, this, &QtGui::on_operation_start_disable_all);
	connect(worker, &DetectorWorker::update_tab, this, &QtGui::update_progress_tab);
}

//OK
void QtGui::on_connect_btn_clicked() {
	QString host_ip = ui.hostIpInput->text();
	char host_ip_c[20];

	if (!isValidIP(host_ip.toStdString())) {
		QMessageBox::warning(this, "Aviso", "Endere\u00E7o de IP inv\u00E1lido.");
		return;
	}

	QMetaObject::invokeMethod(
		worker, "w_connect_detector", 
		Qt::QueuedConnection, Q_ARG(QString, host_ip));
}

//OK
void QtGui::on_device_connect_signal(int num_devices) {
	// Disable ip input and enable device selection
	ui.hostIpInput->setDisabled(true);
	ui.hostIpConnectBtn->setDisabled(true);
	ui.deviceSelect->setDisabled(false);

	for (int i = 0; i < num_devices; i++) {
		ui.deviceSelect->addItem("Dispositivo " + QString::number(i + 1));
	}
}

//OK
void QtGui::on_device_select_changed(int index) {
	// Checando se o dispositivo selecionado é valido
	QString selected_option = ui.deviceSelect->itemText(index);
	int device_index = selected_option.split(" ")[1].toInt() - 1;

	QMetaObject::invokeMethod(
		worker, "w_select_device",
		Qt::QueuedConnection, Q_ARG(int, device_index));
}

//OK
void QtGui::on_device_select_success_signal(
QString d_ip, QString d_type, QString d_mac_address, QString d_firm_ver, 
QString d_cmd_port, QString d_img_port, QString d_serial_num) {

	//colocamos os dados do device na UI
	ui.deviceIpInput->setText(d_ip);
	ui.deviceTypeInput->setText(d_type);
	ui.deviceMacInput->setText(d_mac_address);
	ui.deviceFirmwareInput->setText(d_firm_ver);
	ui.deviceCmdPortInput->setText(d_cmd_port);
	ui.deviceImgPortInput->setText(d_img_port);
	ui.deviceSerialInput->setText(d_serial_num);

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

	//por fim, garantimos que "tomografia" e "imagecombobox" estejam selecionados por padrão
	ui.acquisitionModeInput->setCurrentIndex(0);
	ui.imageQuantityStackedWidget->setCurrentIndex(0);
}

//TODO
void QtGui::on_device_info_update_btn_clicked() {
	int device_id = ui.deviceSelect->currentIndex() - 1;

	QString ip = ui.deviceIpInput->text();
	QString cmd_port = ui.deviceCmdPortInput->text();
	QString img_port = ui.deviceImgPortInput->text();

	/*this->xdevice_ptr->SetIP(ip.toStdString().c_str());
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
	}*/
}

//OK
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

//TODO (não existe lógica relacionada a raspberrypi ainda)
void QtGui::on_mechanical_mode_changed(int index) {
	QString selected_mechanical_mode = ui.mechanicalModeInput->itemText(index);

	if (selected_mechanical_mode == QString("Arduino")) {

	}
	else {

	}

	return;
}

//OK
void QtGui::on_mechanical_connect_btn_clicked() {
	QString selected_mechanical_mode = ui.mechanicalModeInput->currentText();

	if (selected_mechanical_mode == QString("Arduino")) {
		QMetaObject::invokeMethod(
			worker, "w_arduino_connect_serial_port",
			Qt::QueuedConnection);
	}
	else {
		/*QMetaObject::invokeMethod(
			worker, "w_raspberry_connect",
			Qt::QueuedConnection);*/
	}

	return;
}

//OK
void QtGui::on_binning_mode_changed(int index) {
	QString selected_binning_mode = ui.binningModeInput->itemText(index);
	int binning_mode = selected_binning_mode.toStdString() == "Normal" ? 0: 1;

	QMetaObject::invokeMethod(
		worker, "w_binning_mode_change",
		Qt::QueuedConnection, Q_ARG(int, binning_mode)
	);
}

//OK
void QtGui::on_gain_mode_changed(int index) {
	QString selected_gain_mode = ui.gainModeInput->itemText(index);
	int gain_mode = selected_gain_mode.toStdString() == "Alto" ? 256 : 1;

	QMetaObject::invokeMethod(
		worker, "w_gain_mode_change",
		Qt::QueuedConnection, Q_ARG(int, gain_mode)
	);
}

//OK
void QtGui::on_integration_time_changed() {
	int integration_time = ui.integrationTimeInput->text().toInt();

	if (integration_time < 1) {
		QMessageBox::warning(this, "Aviso", "O tempo de integra\u00E7\u00E3o deve ser maior que 0s.");
		ui.integrationTimeInput->setText("1000000");
		integration_time = 1000000;
	}

	QMetaObject::invokeMethod(
		worker, "w_integration_time_change",
		Qt::QueuedConnection, Q_ARG(int, integration_time)
	);
}

//OK
void QtGui::on_integration_time_signal(uint64_t integration_time) {
	ui.integrationTimeInput->setText(QString::number(integration_time));
	set_total_approximate_time();
}

//OK
void QtGui::on_interval_time_changed() {
	int interval_time = ui.intervalTimeInput->text().toInt();

	if (interval_time < 0) {
		QMessageBox::warning(this, "Aviso", "O tempo de intervalo deve ser maior que ou igual a 0s.");
		ui.intervalTimeInput->setText("1500");
	}

	set_total_approximate_time();
}

//OK
void QtGui::on_image_quantity_combobox_changed(int index) {
	QString selected_image_quantity = ui.imageQuantityComboBox->itemText(index);
	int image_quantity = selected_image_quantity.toInt();

	set_total_approximate_time();
}

//OK
void QtGui::on_image_quantity_input_changed() {
	int image_quantity = ui.imageQuantityInput->text().toInt();

	if (image_quantity < 1) {
		QMessageBox::warning(this, "Aviso", "A quantidade de imagens deve maior que 0.");
		ui.imageQuantityInput->setText("5");
	}

	set_total_approximate_time();
}

//OK?
void QtGui::on_file_prefix_input_changed() {
	QString file_prefix= ui.filePrefixInput->text();

	if (file_prefix.toStdString() == "") {
		QMessageBox::warning(this, "Aviso", "O prefixo n\u00E3o pode ser vazio.");
		ui.filePrefixInput->setText("img");
		return;
	}
}

//OK?
void QtGui::on_choose_file_path_btn_clicked() {
	this->file_path = QFileDialog::getExistingDirectory(this, "Escolha um diretório", "C:/");
	ui.filePathInput->setText(this->file_path);
}

//TODO
void QtGui::on_grab_btn_clicked() {
	
	string file_path = ui.filePathInput->text().toStdString();
	string file_prefix = ui.filePrefixInput->text().toStdString();
	int total_approximate_time = get_total_approximate_time();

	if (file_prefix == "" || file_path == "" || total_approximate_time <= 0) {
		QMessageBox::warning(this, "Aviso", "Preencha todos os campos antes de iniciar a opera\u00E7\u00E3o.");
		return;
	}
	
	//precisa checar também os parametros direto pelo dispositivo:
	string acquisition_mode = ui.acquisitionModeInput->currentText().toStdString();
	string mechanical_mode = ui.mechanicalModeInput->currentText().toStdString();
	if (mechanical_mode == "Arduino") {
		bool arduino_is_open;
		QMetaObject::invokeMethod(worker, "w_arduino_check_open",
			Qt::DirectConnection, Q_RETURN_ARG(bool, arduino_is_open));

		if (!arduino_is_open) {
			QMessageBox::warning(this, "Erro", "Porta serial não está aberta.");
			return;}
	}

	int interval_time = ui.intervalTimeInput->text().toInt();
	int image_quantity = 0;
	if (acquisition_mode == "Tomografia") {
		image_quantity = ui.imageQuantityComboBox->currentText().toInt();
	}
	else {
		image_quantity = ui.imageQuantityInput->text().toInt();
	}

	QMessageBox::information(this, "Dispositivo pronto", "clique no bot\u00E3o para iniciar a opera\u00E7\u00E3o");
	on_operation_start_disable_all();

	QMetaObject::invokeMethod(
		worker, "w_grab_start_operation",
		Qt::QueuedConnection, 
		Q_ARG(QString, QString::fromStdString(acquisition_mode)),
		Q_ARG(QString, QString::fromStdString(mechanical_mode)),
		Q_ARG(int, interval_time),
		Q_ARG(int, image_quantity),
		Q_ARG(QString, QString::fromStdString(file_path)),
		Q_ARG(QString, QString::fromStdString(file_prefix)),
		Q_ARG(int, total_approximate_time)
	);
}

//OK
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

//OK
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

//TODO
void QtGui::on_stop_grab_btn_clicked() {
	/*this->stop_bnt_pressed = true;
	this->xacquisition.Stop();
	on_operation_end_enable_all();*/
}

//TODO
void QtGui::update_progress_tab(int index, int total_images, time_t starting_time, 
QString file_path, QString file_prefix)
{
	
	//EXIBINDO
	QString current_displayed_string = QString("Exibindo: %1%2.dat")
		.arg(file_prefix)
		.arg(index, 1, 10, QChar('0'));
	if (index == 0) {
		current_displayed_string = QString("Exibindo: ---");
	}
	ui.currentDisplayedImageLabel->setText(current_displayed_string);

	//PROCESSANDO
	QString processing_string = QString("Processando: %1%2.dat")
		.arg(file_prefix)
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
		QString image_path = (file_path + "/" + file_prefix + QString::number(index + 1) + ".dat");
		update_displayed_image(image_path);
	}

	//STOP BUTTON
	if(this->stop_bnt_pressed == true)
		status_string = QString("Status: Parado");
}

//TODO
void QtGui::update_displayed_image(QString image_path) {
	int width = 1400;
	int height = 1200;
	int total_size = width * height;
	
	QFile file(image_path);
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

//TODO
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

//TODO
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


QtGui::~QtGui()
{}
