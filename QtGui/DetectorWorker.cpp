#include "DetectorWorker.h"

#include "QtDebug"
#include "QMessageBox"
#include "QFileDialog"
#include <QFile>
#include <QTextStream>

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

////The allocated buffer size for the grabbed frames
//#if defined(_WIN64)
//uint32_t frame_buffer_size = 700;
//#else
//uint32_t frame_buffer_size = 400;
//#endif



DetectorWorker::DetectorWorker(QObject* parent) 
	: QObject(parent),
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
	serial = new QSerialPort(this);
	
}

void DetectorWorker::w_recebido() {
	//emit retornando();
}

//OK
void DetectorWorker::w_connect_detector(QString ip) {

	w_escrever_mensagem_t("log.txt", "Entrou na thread secundaria");
	// Create objects
	QByteArray ipBytes = ip.toLocal8Bit();
	this->xsystem = new XSystem(ipBytes.constData());

	this->xsystem->RegisterEventSink(this->cmd_sink);

	this->xcommand.RegisterEventSink(this->cmd_sink);

	this->xtransfer.RegisterEventSink(this->img_sink);

	this->xacquisition.RegisterEventSink(this->img_sink);
	this->xacquisition.RegisterFrameTransfer(&this->xtransfer);

	// Open system connection
	if (!this->xsystem->Open()) {
		emit message_box_error("Erro", ("Falha ao conectar ao host " + QString(ip) + "."));
		return;
	}

	// Find device
	int num_devices = this->xsystem->FindDevice();
	if (num_devices <= 0) {
		emit message_box_warning("Aviso", "Nenhum dispositivo encontrado.");
		return;
	}

	emit device_conection_success(num_devices);

	emit message_box_info("Status", "Conectado com sucesso ao host " + QString(ip) + ".");
}

//OK
void DetectorWorker::w_device_select(int device_index) {
	if (this->xdevice_ptr != nullptr) {
		this->xcommand.Close();
		this->xacquisition.Close();
		this->xdevice_ptr = nullptr;
	}

	//Checando se dispositivo é válido
	this->xdevice_ptr = this->xsystem->GetDevice(device_index);
	if (!this->xdevice_ptr) {
		emit message_box_error("Erro", "Dispositivo invalido");
		return;
	}

	//O dispositivo selecionado é válido, então vamos estabelecer conexão com as portas
	// Open command connection
	if (!this->xcommand.Open(this->xdevice_ptr)) {
		emit message_box_error("Erro", "Falha ao abrir o canal de comando.");
		return;
	}

	// Open acquisition connection
	if (!this->xacquisition.Open(this->xdevice_ptr, &this->xcommand)) {
		emit message_box_error("Erro", "Falha ao abrir o canal de aquisi\u00E7\u00E3o.");
		return;
	}

	//comunicação estabelecida, agora, passamos os dados pra thread principal
	QString device_ip = QString(this->xdevice_ptr->GetIP());
	QString device_type = QString(this->xdevice_ptr->GetDeviceType());
	uint8_t* mac = this->xdevice_ptr->GetMAC();
	QString device_mac_address = QString("%1:%2:%3:%4:%5:%6")
		.arg(mac[0], 2, 16, QChar('0'))
		.arg(mac[1], 2, 16, QChar('0'))
		.arg(mac[2], 2, 16, QChar('0'))
		.arg(mac[3], 2, 16, QChar('0'))
		.arg(mac[4], 2, 16, QChar('0'))
		.arg(mac[5], 2, 16, QChar('0'));
	QString device_firm_ver = QString::number(this->xdevice_ptr->GetFirmVer());
	QString device_cmd_port = QString::number(this->xdevice_ptr->GetCmdPort());
	QString device_img_port = QString::number(this->xdevice_ptr->GetImgPort());
	QString device_serial_num = QString(this->xdevice_ptr->GetSerialNum());

	emit device_select_success(device_ip, device_type, device_mac_address, device_firm_ver,
		device_cmd_port, device_img_port, device_serial_num);

	//e definimos alguns valores padrões para o dispositivo
	if (this->xcommand.SetPara(XPARA_BINNING_MODE, 0) != 1)
	{
		emit message_box_error("Erro", "Falha ao definir o modo de binning.");
	}

	if (this->xcommand.SetPara(XPARA_GAIN_RANGE, 1) != 1)
	{
		emit message_box_error("Erro", "Falha ao definir o modo de ganho.");
	}

	if (this->xcommand.SetPara(XPARA_FRAME_PERIOD, 1000000) != 1)
	{
		emit message_box_error("Erro", "Falha ao definir o tempo de integra\u00E7\u00E3o.");
	}
}

//OK
void DetectorWorker::w_arduino_connect_serial_port() {
	if (serial->isOpen())
		serial->close();

	serial->setPortName("COM4");
	serial->setBaudRate(QSerialPort::Baud9600);
	serial->setDataBits(QSerialPort::Data8);
	serial->setParity(QSerialPort::NoParity);
	serial->setStopBits(QSerialPort::OneStop);
	serial->setFlowControl(QSerialPort::NoFlowControl);

	if (!serial->open(QIODevice::WriteOnly)) {
		emit message_box_error("Erro:", "N\u00E3o foi possível abrir a porta serial:\n" + serial->errorString());
	}
	else {
		emit message_box_info("Status:", "Conex\u00E3o estabelecida com o arduino.");
	}
}

//OK
void DetectorWorker::w_binning_mode_change(int binning_mode) {
	if (!this->xcommand.SetPara(XPARA_BINNING_MODE, binning_mode))
	{
		emit message_box_error("Erro", "Falha ao definir o modo de binning");
	}
}

//OK
void DetectorWorker::w_gain_mode_change(int gain_mode) {
	if (!this->xcommand.SetPara(XPARA_GAIN_RANGE, gain_mode))
	{
		emit message_box_error("Erro", "Falha ao definir o modo de ganho");
	}
}

//OK
void DetectorWorker::w_integration_time_change(int integration_time) {
	if (!this->xcommand.SetPara(XPARA_FRAME_PERIOD, integration_time))
	{
		emit message_box_error("Erro", "Falha ao definir o tempo de integra\u00E7\u00E3o.");
		emit integration_time_change_end(0);
		return;
	}
	
	uint64_t frame_period;
	this->xcommand.GetPara(XPARA_FRAME_PERIOD, frame_period);
	emit integration_time_change_end(frame_period);
}

void DetectorWorker::w_grab_start_operation(
QString acquisition_mode, QString mechanical_mode, int interval_time, int image_quantity,
QString file_path, QString file_prefix, time_t total_time)
{
	this->stop_bnt_pressed == false;
	time_t starting_time = time(nullptr);
	float angle = 360.0f / float(image_quantity);
	time_t remaining_time = total_time;
	w_escrever_inicio_log("log.txt", acquisition_mode, mechanical_mode, interval_time, image_quantity, file_path, file_prefix);


	//INICIO OPERACAO
	for (int i = 0; i < image_quantity && !stopRequested.load(); i++) {
		emit update_tab(i, image_quantity, starting_time, remaining_time, file_path, file_prefix);

		QString inicioCicloX = " - Iniciando ciclo " + QString::number(i + 1);
		w_escrever_mensagem_t("log.txt", inicioCicloX);

		this->set_is_save(true);
		this->set_frame_count(0);
		this->set_lost_frame_count(0);
		this->set_save_file_name(file_path.toStdString() + "/" + file_prefix.toStdString() + to_string(i + 1) + ".dat");

		if (!this->ximg_handle.OpenFile(this->save_file_name.c_str()))
		{
			emit message_box_error("Erro de conexao", "Falha ao abrir o arquivo de imagem.");
			emit enable_all();
			return;
		}

		this->xacquisition.Grab(1);
		this->xevent.Wait();
		this->ximg_handle.CloseFile();

		QString imgCapturadoX = " - " + file_prefix + QString::number(i + 1) + ".dat capturado";
		w_escrever_mensagem_t("log.txt", imgCapturadoX);


		if (acquisition_mode == "Tomografia") {
			w_arduino_send_command("1");
			Sleep(250);
			w_arduino_send_command(std::to_string(angle));
			w_escrever_mensagem_t("log.txt", ("Rotacionando a amostra em " + QString::number(angle) + " graus"));
		}
		QString fimCicloX = " - Finalizando ciclo " + QString::number(i + 1) + "\n";
		w_escrever_mensagem_t("log.txt", fimCicloX);
		Sleep(interval_time);

		remaining_time = w_calcular_tempo_restante(image_quantity, i + 1, starting_time);
	}

	if(stopRequested.load())
		w_escrever_mensagem_t("log.txt", "Botao de parada acionado");

	QString fimOperacao = " - Finalizando operacao " + file_prefix + ".dat \n";
	w_escrever_mensagem_t("log.txt", fimOperacao);

	emit update_tab(image_quantity, image_quantity, starting_time, remaining_time, file_path, file_prefix);
	
	stopRequested.store(false);

	emit message_box_info("Aquisi\u00E7\u00E3o", "Opera\u00E7\u00E3o completa.");
	emit enable_all();
}

void DetectorWorker::w_grab_stop_operation() {
	this->xacquisition.Stop();
	this->stop_bnt_pressed = true;
	w_escrever_mensagem_t("log.txt", "Botao de parada acionado");
}


bool DetectorWorker::w_arduino_check_open() {
	return (serial->isOpen());
}

//OK
void DetectorWorker::w_arduino_send_command(const std::string& comando) {
	if (!serial->isOpen()) {
		emit message_box_error("Erro na porta serial", "Porta serial nao esta aberta");
		return;
	}

	serial->write((comando + "\n").c_str());
	serial->waitForBytesWritten(1000);
	serial->flush();

	QString arduinoComando =
		QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]") +
		" - Enviando comando '" + QString::fromStdString(comando) + "' ao arduino " + "\n";
	w_escrever_mensagem_t("log.txt", arduinoComando);
}



//OK
void DetectorWorker::w_escrever_mensagem(const QString& caminhoArquivo, const QString& mensagem) {
	QFile arquivo(caminhoArquivo);
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

void DetectorWorker::w_escrever_mensagem_t(const QString& caminhoArquivo, const QString& mensagem) {
	
	QString mensagemFormatada =
		QDateTime::currentDateTime().toString("[yyyy/MM/dd hh:mm:ss]") + mensagem;
	w_escrever_mensagem(caminhoArquivo, mensagemFormatada);
}


//OK
void DetectorWorker::w_escrever_inicio_log(
const QString& caminho_arquivo, QString acquisition_mode, QString mechanical_mode, int interval_time,
int image_quantity, QString file_path, QString file_prefix)
{
	w_escrever_mensagem_t(caminho_arquivo, "Iniciando operacao " + file_prefix + ".dat");

	uint64_t binning;
	if (this->xcommand.GetPara(XPARA_BINNING_MODE, binning) != 1)
	{
	}
	QString binning_mode = (binning == 0 ? "Normal" : "2x2");

	uint64_t gain;
	if (this->xcommand.GetPara(XPARA_GAIN_RANGE, gain) != 1)
	{
	}
	QString gain_mode = (gain == 0 ? "Low" : "High");

	uint64_t integration;
	if (this->xcommand.GetPara(XPARA_FRAME_PERIOD, integration) != 1)
	{
	}
	QString integration_time = QString::number(integration);

	QString logText =
		"Parametros da Operacao:" "\n"
		"Modo de Aquisicao: " + acquisition_mode + "\n" +
		(acquisition_mode == "Tomografia" ? 
			("Mecanismo de Rotacao: " + mechanical_mode + "\n") : ("")) +
		"Modo de Binning: " + binning_mode + "\n" +
		"Modo de Ganho: " + gain_mode + "\n" +
		"Tempo de Integracao (us): " + integration_time + "\n" +
		"Tempo de Intervalo (ms): " + QString::number(interval_time) + "\n" +
		"Quantidade de Imagens: " + QString::number(image_quantity) + "\n" +
		"Prefixo: " + file_prefix + "\n" +
		"Diretorio: " + file_path + "\n";

	w_escrever_mensagem(caminho_arquivo, logText);
}


time_t DetectorWorker::w_calcular_tempo_restante(int img_total, int img_processadas, time_t starting_time) {	
	time_t elapsed_time_t = time(nullptr) - starting_time;
	time_t total_time_t = ((elapsed_time_t * img_total) / img_processadas);
	time_t remaining_time_t = total_time_t - elapsed_time_t;

	return remaining_time_t;
}

time_t DetectorWorker::w_calcular_tempo_total_esperado(int img_total, int integration_time, int interval_time, QString acquisition_mode) {
	
	float mechanical_signal_time = 0;
	if (acquisition_mode == "Tomografia")
		mechanical_signal_time = 0.25;

	time_t approximate_time = img_total * ((integration_time * 3.0) / 1000000 + (interval_time * 1.0) / 1000 + mechanical_signal_time);
		return approximate_time;

}

void DetectorWorker::set_frame_count(uint32_t frame_count) {
	this->frame_count = frame_count;
}

void DetectorWorker::set_lost_frame_count(uint32_t lost_frame_count) {
	this->lost_frame_count = lost_frame_count;
}

void DetectorWorker::set_is_save(bool is_save) {
	this->is_save = is_save;
}

void DetectorWorker::set_save_file_name(std::string save_file_name) {
	this->save_file_name = save_file_name;
}

uint32_t DetectorWorker::get_frame_count() {
	return this->frame_count;
}

uint32_t DetectorWorker::get_lost_frame_count() {
	return this->lost_frame_count;
}

bool DetectorWorker::get_is_save() {
	return this->is_save;
}

std::string DetectorWorker::get_save_file_name() {
	return this->save_file_name;
}

XImageHandler* DetectorWorker::get_ximage_handler() {
	return &ximg_handle;
}

XEvent* DetectorWorker::get_xevent()
{
	return &this->xevent;
}

DetectorWorker::~DetectorWorker() {
	delete cmd_sink;
	delete img_sink;
}