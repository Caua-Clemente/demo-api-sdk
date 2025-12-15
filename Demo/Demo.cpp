// Demo.cpp
// A C++ example of the usage of X-LIB
#include "stdafx.h"

//include X-LIB headers
#include "xsystem.h"
#include "xdevice.h"
#include "xcommand.h"

#include "xacquisition.h"
#include "xframe_transfer.h"
#include "xgig_factory.h"

#include "ixcmd_sink.h"
#include "iximg_sink.h"

#include "ximage_handler.h"
#include "xcorrection.h"

#ifdef _MSC_VER
#include "xthread_win.h"
#else
#include "xthread_liu.h"
#endif

#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <locale>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>
#include <windows.h>

#ifdef _WIN64
#pragma comment(lib, "..\\lib\\x64\\XLibDllKosti.lib")
#else
#pragma comment(lib, "..\\lib\\x86\\XLibDllKosti.lib")
#endif

#include <string>
#include <thread> 
#include <fstream>

using namespace std;

//Global variables

XImageHandler ximg_handle; // XImageHandler object
XEvent frame_complete; // XEvent object

uint32_t frame_count = 0; // Number of frames grabed
uint32_t lost_frame_count = 0; // Number of lost frames

bool is_save = 0; // Flag for saving frames
string save_file_name; // Name of the saved file

//The allocated buffer size for the grabbed frames
#if defined(_WIN64)
uint32_t frame_buffer_size = 700;
#else
uint32_t frame_buffer_size = 400;
#endif

//Function prototypes

void displayMenuPrincipal();
void clearBuffer();
uint64_t getImageAverage(string file_name);
HANDLE abrirPortaSerial(const char* porta);
void enviarComando(HANDLE hSerial, const std::string& comando);
bool checarAngulo(int angulo);

//Uma classe para manipular eventos de comando do dispositivo
class CmdSink :public IXCmdSink
{
public:
	// Manipulação de erro
	// Parâmetros err_id: ID do error, err_msg_: Mensagem de erro
	void OnXError(uint32_t err_id, const char* err_msg_) override
	{
		cout << "OnXError: " << err_id << ", " << err_msg_ << endl;
	}
	// Manipulação de eventos
	// Parâmetros event_id: ID do evento, data: Dados do evento
	// Eventos: _cisTemperature; _dasTemperature1; _dasTemperature2; _dasTemperature3; _dasHumidity;
	void OnXEvent(uint32_t event_id, XHealthPara data) override
	{
		//cout << "On Event ID " << event_id << " data " << data._dasTemperature1 << endl;
	}
};

//Uma classe para manipular eventos de imagem
class ImgSink : public IXImgSink
{
	// Manipulação de erro
	// Parâmetros err_id: ID do error, err_msg_: Mensagem de erro
	void OnXError(uint32_t err_id, const char* err_msg_) override
	{
		printf("OnXERROR: %u, %s\n", err_id, err_msg_);
	}

	// Manipulação de eventos
	// Parâmetros event_id: ID do evento, data: Dados do evento
	// Eventos: XEVENT_IMG_PARSE_DATA_LOST, XEVENT_IMG_TRANSFER_BUF_FULL, XEVENT_IMG_PARSE_DM_DROP,
	//          XEVENT_IMG_PARSE_PAC_LOST, XEVENT_IMG_PARSE_MONITOR_STATUS_ERR
	void OnXEvent(uint32_t event_id, uint32_t data) override
	{
		if (XEVENT_IMG_PARSE_DATA_LOST == event_id)
		{
			lost_frame_count += data;
		}
	}

	// Manipulação de quadros prontos
	// Parâmetros image_: Ponteiro para o quadro
	void OnFrameReady(XImage* image_) override
	{
		printf("\nFrame %u ready, width %u, height %d,  lost line %u\n",
			frame_count++, image_->_width, image_->_height, lost_frame_count);
		Beep( 750, 300 );

		if (is_save)
		{
			ximg_handle.Write(image_);
		}
	}

	// Manipulação de quadros completos
	void OnFrameComplete() override
	{
		printf("Grab complete.\n");

		if (is_save)
		{
			string txt_name = save_file_name.replace(save_file_name.find(".dat"), 4, ".txt");

			ximg_handle.SaveHeaderFile(txt_name.c_str());
			ximg_handle.CloseFile();

			is_save = 0;
		}

		frame_complete.Set();
	}

};

//Um dispositivo "genérico" para simular uma conexão
/*xdevice_ptr = new XDevice(&xsystem);
xdevice_ptr->SetIP("192.168.1.2");
xdevice_ptr->SetCmdPort(3000);
xdevice_ptr->SetImgPort(4001);
xdevice_ptr->SetDeviceType("1412_KOSTI");
xdevice_ptr->SetSerialNum("1234567890", 10);
xdevice_ptr->SetMAC((uint8_t*)"123456");
xdevice_ptr->SetFirmBuildVer(123);
xdevice_ptr->SetFirmVer(123);*/

CmdSink cmd_sink;
ImgSink img_sink;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "pt_BR.UTF-8");

	char host_ip[20];

	if (1 == argc)
	{
		cout << "Por favor, insira o IP do host" << endl;
		cin >> host_ip;
		clearBuffer();
		cout << endl;
	}

	else
	{
		memcpy(host_ip, argv[1], 20);
	}

	XSystem xsystem(host_ip);
	XDevice* xdevice_ptr = NULL;

	int32_t device_count = 0;
	char device_ip[20];

	uint16_t device_cmd_port;
	uint16_t device_img_port;

	xsystem.RegisterEventSink(&cmd_sink);

	XGigFactory xfactory;

	XCommand xcommand(&xfactory);
	xcommand.RegisterEventSink(&cmd_sink);

	XFrameTransfer xtransfer;
	xtransfer.RegisterEventSink(&img_sink);

	XAcquisition xacquisition(&xfactory);

	xacquisition.RegisterEventSink(&img_sink);
	xacquisition.RegisterFrameTransfer(&xtransfer);

	XCorrection xcorrection;

	string send_str;
	string recv_str;

	int input_char;

	string offset_file;
	string gain_file;
	string img_file;

	uint64_t cmd_para = 0;

	//For cycling test
	uint32_t cycle_num = 1;
	uint32_t frame_num = 1;
	uint32_t cycle_interval = 0;
	int32_t cycle_it = 0;
	int32_t frame_interval = 0;

	//Arduino Connection
	const char* portaSerial = "\\\\.\\COM4";
	HANDLE hSerial = abrirPortaSerial(portaSerial);
	if (hSerial == INVALID_HANDLE_VALUE) {
		cout << "Falha na conexão com o arduino\n\n";
	}
	else {
		cout << "Conexão estabelecida com o Arduino\n\n";
	}

	displayMenuPrincipal();

	do
	{
		cout << "Por favor, escolha uma opção: ";
		input_char = getchar();
		clearBuffer();
		cout << endl;

		switch (input_char)
		{
		case '1': //Encontrar dispositivo

			if (!xsystem.Open())
			{
				cerr << "Falha ao conectar ao host." << endl;
    			return 0;  // Termina a execução se não conseguir conectar
			}
			
			device_count = xsystem.FindDevice(); // device_count = 1;
			
			if (device_count <= 0)
			{
				cout << "Nenhum dispositivo encontrado." << endl;
				return 0;
			}

			xdevice_ptr = xsystem.GetDevice(0); //Get the first device

			cout << "Dispositivo encontrado: " << xdevice_ptr->GetIP() << endl;
			cout << "Porta de comando: " << xdevice_ptr->GetCmdPort() << endl;
			cout << "Porta de imagem: " << xdevice_ptr->GetImgPort() << endl;

			break;


		case '2': // Abrir dispositivo
			if (xcommand.Open(xdevice_ptr))
			{
				cout << "Canal de comando aberto com sucesso" << endl;

				if (xacquisition.Open(xdevice_ptr, &xcommand))
				{
					cout << "Canal de imagem aberto com sucesso" << endl;
					
					//Definindo configurações padrão
					if (1 != xcommand.SetPara(XPARA_GAIN_RANGE, 1)) //Definindo Ganho como LOW
						cout << "Falha ao definir o ganho\n\n";

					
					//Integration time é o tempo que o dispositivo detecta radiação para construir a imagem
					if (1 != xcommand.SetPara(XPARA_FRAME_PERIOD, 10000000)) //Definindo Integration Time como 10000000 us
						cout << "Falha ao definir o tempo de integração" << endl << endl;

					//Frame interval é o intervalo entre a finalização de captura de imagem e o início de outra captura
					frame_interval = 3000; //Definindo frame interval como 3 segundos.

					frame_num = 1;
					cycle_num = 1;

					//Falta definir o modo de binning

				}
				else
					cout << "Falha ao abrir o canal de imagem" << endl;
			}

			else
				cout << "Falha ao abrir o canal de comando" << endl;

			break;


		case '3': { //Capturar n imagens (sem rotação)
			int numeroFramesMax;
			string prefix;
			string file_directory;

			cout << "Digite a quantidade de imagens:\n";
			cin >> numeroFramesMax;
			clearBuffer();

			cout << "Digite o nome prefixo dos arquivos:\n";
			cin >> prefix;
			clearBuffer();

			cout << "Digite o nome da pasta diretório para os arquivos\n";
			cin >> file_directory;
			clearBuffer();

			cout << "Esperando 4 segundos (segurança)" << endl;
			Sleep(4000);

			for (int i = 1; i <= numeroFramesMax; i++) {
				frame_count = 0;
				lost_frame_count = 0;
				is_save = 1;

				std::cout << endl << endl << "----------------------" << endl;
				save_file_name = (file_directory + "/" + prefix + (std::to_string(i)) + ".dat");

				if (!ximg_handle.OpenFile(save_file_name.c_str()))
				{
					cout << "Falha ao abrir o arquivo de imagem, retornando ao menu principal" << endl;
					break;
				}

				std::cout << "Grabbing " << save_file_name << std::endl;
				xacquisition.Grab(1); //O detector abre para receber radiação e em paralelo começa a construir a imagem
				std::cout << "Shooting " << std::endl;
				frame_complete.Wait(); //O programa espera a imagem terminar de ser construída
				ximg_handle.CloseFile(); //Faz o imghandler liberar a imagem

				std::cout << endl << "----------------------" << endl;
				std::cout << "Esperando " << frame_interval << " milissegundos...";
				Sleep(frame_interval);
			}

			cout << endl << "Captura de imagens finalizada" << endl;
			break;
		}


		case '4': { //Iniciar tomografia

			int numeroFramesMax;
			float angle_variation;
			string prefix;
			string file_directory;
			
			cout << "Digite a quantidade de imagens para o ensaio\n";
			cin >> numeroFramesMax;
			clearBuffer();

			angle_variation = 360 / numeroFramesMax; 
			if (!checarAngulo(angle_variation)) {
				cout << "Numero de frames inválido. Voltando ao menu principal\n\n";
				break;
			}

			cout << "Digite o nome prefixo dos arquivos:\n";
			cin >> prefix;
			clearBuffer();

			cout << "Digite o nome da pasta diretório para os arquivos\n";
			cin >> file_directory;
			clearBuffer();

			cout << "Esperando 4 segundos (segurança)" << endl;
			Sleep(4000);

			for (int i = 1; i <= numeroFramesMax; i++) {
				frame_count = 0;
				lost_frame_count = 0;
				is_save = 1;

				std::cout << endl << endl << "----------------------" << endl;
				save_file_name = (file_directory + "/" + prefix + (std::to_string(i)) + ".dat");

				if (!ximg_handle.OpenFile(save_file_name.c_str()))
				{
					cout << "Falha ao abrir o arquivo de imagem, retornando ao menu principal" << endl;
					break;
				}

				std::cout << "Grabbing " << save_file_name << std::endl;
				xacquisition.Grab(1); //O detector abre para receber radiação e em paralelo começa a construir a imagem
				std::cout << "Shooting " << std::endl;
				frame_complete.Wait(); //O programa espera a imagem terminar de ser construída
				ximg_handle.CloseFile(); //Faz o imghandler liberar a imagem

				enviarComando(hSerial, "1"); //Manda rotacionar a amostra
				Sleep(1000); //espera para não dar conflito de sinal
				enviarComando(hSerial, std::to_string(angle_variation)); //manda o angulo para rotação
				std::cout << endl << "----------------------" << endl;
				std::cout << "Esperando " << frame_interval << " milissegundos...";
				Sleep(frame_interval);
			}

			cout << endl << "Tomografia finalizada" << endl;
			break;
		}


		case '5': //Fechar dispositivo
			cout << "Fechando o dispositivo" << endl;

			xacquisition.Close();

			xcommand.Close();

			break;


		case '6': { //Exibir configuração atual
			string str_integracao;
			if (1 == xcommand.GetPara(XPARA_FRAME_PERIOD, str_integracao))
				cout << "Tempo de Integracao: " << str_integracao << endl;
			else
				cout << "Falha ao exibir tempo de integração" << endl;

			string str_espera = std::to_string(frame_interval);
			cout << "Tempo de Espera: " << str_espera << endl;
			

			string str_gain;
			if (1 == xcommand.GetPara(XPARA_GAIN_RANGE, str_gain))
				cout << "Modo de Ganho: " << str_gain << endl;
			else
				cout << "Falha ao exibir modo de ganho" << endl;

			string str_binning;
			if (1 == xcommand.GetPara(XPARA_BINNING_MODE, str_binning))
				cout << "Modo de Binning: " << str_binning << endl;
			else
				cout << "Falha ao exibir modo de binning" << endl;

			break;
		}


		case '7': //Restaurar configurações padrão

			//Definindo Integration Time como 10000000 us
			if (1 == xcommand.SetPara(XPARA_FRAME_PERIOD, 10000000))
			{
				cout << "Tempo de integração (=10000000 us) definido com sucesso" << endl << endl;
			}
			else
			{
				cout << "Falha ao definir o tempo de integração" << endl << endl;
			}

			//Tempo Espera
			frame_interval = 3000;
			cout << "Tempo de espera (=3000 ms) definido com sucesso" << endl << endl;

			//Definindo Ganho como LOW
			if (1 == xcommand.SetPara(XPARA_GAIN_RANGE, 1))
			{
				cout << "Ganho (=Low) definido com sucesso\n\n";
			}
			else
			{
				cout << "Falha ao definir o ganho\n\n";
			}


			//Definindo 1 frame, 1 numero de ciclo, x ms de cycle interval
			frame_num = 1;
			cycle_num = 1;

			cout << "Numero de frame por ciclo (1) definido com sucesso" << endl;
			cout << "Numero de ciclos (1) definido com sucesso" << endl;
			break;


		case 'I': //Tempo de Integração
		case 'i':
			cout << "Por favor insira o tempo de integração (us)" << endl;
			cin >> cmd_para;

			if (1 == xcommand.SetPara(XPARA_FRAME_PERIOD, cmd_para))
			{
				cout << "Tempo de integração definido com sucesso" << endl << endl;
			}
			else
			{
				cout << "Falha ao definir o tempo de integração" << endl << endl;
			}

			clearBuffer();

			break;


		case 'E': //Tempo de Espera
		case 'e':
			cout << "Por favor insira o tempo de espera (ms)" << endl;
			cin >> frame_interval;
			cout << "Tempo de espera definido com sucesso" << endl << endl;
			clearBuffer();

			break;


		case 'G': //Modo de Ganho
		case 'g':
			cout << "Por favor insira o modo de ganho: \n 1: Baixo ganho\n 256: Alto ganho\n";
			cin >> cmd_para;

			if (1 == xcommand.SetPara(XPARA_GAIN_RANGE, cmd_para))
			{
				cout << "Ganho definido com sucesso\n\n";
			}
			else
			{
				cout << "Falha ao definir o ganho\n\n";
			}

			clearBuffer();

			break;


		case 'B': //Modo de Binning
		case 'b':
			cout << "Por favor insira o modo de binning: \n 0: Original \n 1: 2x2\n";
			cin >> cmd_para;

			if (1 == xcommand.SetPara(XPARA_BINNING_MODE, cmd_para))
			{
				cout << "Modo de binning definido com sucesso\n\n";
			}
			else
			{
				cout << "Falha ao definir o modo de binning\n\n";
			}

			clearBuffer();

			break;


		case 9: //Configurar conexão do dispositivo
			cout << "Por favor, insira o IP do dispositivo" << endl;
			cin >> device_ip;

			cout << "Por favor, insira a porta de comando do dispositivo" << endl;
			cin >> device_cmd_port;

			cout << "Por favor, insira a porta de imagem do dispositivo" << endl;
			cin >> device_img_port;

			if (xdevice_ptr)
			{
				xdevice_ptr->SetIP(device_ip);
				xdevice_ptr->SetCmdPort(device_cmd_port);
				xdevice_ptr->SetImgPort(device_img_port);
			}

			if (1 == xsystem.ConfigureDevice(xdevice_ptr))
			{
				cout << "Dispositivo configurado com sucesso, por favor, encontre o dispositivo novamente" << endl;
			}
			else
			{
				cout << "Falha ao configurar o dispositivo" << endl;
			}

			break;

		default:
			break;

		}

	} while ((input_char != '0'));


	xacquisition.Close();

	xcommand.Close();

	xsystem.Close();

	CloseHandle(hSerial);

	return 1;
}

void displayMenuPrincipal()
{
	cout << "Bem-vindo ao programa de demonstração do X-LIB\n";
	cout << "Por favor, escolha uma opção a partir das seguintes: \n\n";

	cout << "1- Encontrar dispositivo\n";
	cout << "2- Abrir dispositivo\n";
	cout << "3- Capturar n imagens (sem rotação)\n";
	cout << "4- Iniciar Tomografia\n";
	cout << "5- Fechar dispositivo\n\n";

	cout << "6- Exibir configuração atual\n";
	cout << "7- Restaurar configurações padrão\n";
	cout << "I- Tempo de Integração\n";
	cout << "E- Tempo de Espera\n";
	cout << "G- Modo de Ganho\n";
	cout << "B- Modo de Binning\n";
	cout << "C- Parâmetros de Ciclo\n\n";

	cout << "9- Configurar conexão do dispositivo\n";
	cout << "0- Sair do programa\n\n";
}


void clearBuffer() {
	cin.ignore(10000, '\n');
}

HANDLE abrirPortaSerial(const char* porta) {
	HANDLE hSerial = CreateFileA(porta, GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		std::cerr << "Erro ao abrir a porta serial!" << std::endl;
		return INVALID_HANDLE_VALUE;
	}

	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(hSerial, &dcbSerialParams)) {
		std::cerr << "Erro ao obter configurações da porta serial!" << std::endl;
		CloseHandle(hSerial);
		return INVALID_HANDLE_VALUE;
	}

	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!SetCommState(hSerial, &dcbSerialParams)) {
		std::cerr << "Erro ao configurar a porta serial!" << std::endl;
		CloseHandle(hSerial);
		return INVALID_HANDLE_VALUE;
	}

	return hSerial;
}

void enviarComando(HANDLE hSerial, const std::string& comando) {
	if (hSerial == INVALID_HANDLE_VALUE) return;

	std::string comandoFinal = comando + "\n";
	DWORD bytesEnviados;
	WriteFile(hSerial, comandoFinal.c_str(), comandoFinal.length(), &bytesEnviados, NULL);
	std::cout << "Comando enviado: " << comando << std::endl;
}

uint64_t getImageAverage(string file_name) {
	std::ifstream imagemDat;

	imagemDat.open(file_name, std::ios::binary);
	if (!imagemDat.good()) {
		return 0;
	}

	uint64_t soma_total = 0;
	uint16_t valor;

	for (int y = 0; y < 1200; y++) {
		for (int x = 0; x < 1400; x++) {
			imagemDat.read(reinterpret_cast<char*>(&valor), sizeof(valor));
			soma_total += valor;
		}
	}

	imagemDat.close();

	uint64_t media = soma_total / (1400 * 1200);
	return media;
}

bool checarAngulo(int angulo) {
	float angs_validos[] = {
		0.225,
		0.45,
		0.9,
		1.125,
		1.8,
		2.25,
		3.6,
		4.5,
		5.625,
		7.2,
		9,
		11.25,
		14.4,
		18,
		22.5,
		36,
		45,
		72,
		90, //no repositório tava 70, mas imagino que era pra ser 90
		180
	};

	int tamanho = 20; //angs_validos.size(), ver isso depois


	for (int i = 0; i < tamanho; i++) {
		if (angulo == angs_validos[i])
			return true;
	}

	return false;

}

