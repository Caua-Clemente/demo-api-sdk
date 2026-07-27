#pragma once

#include <QObject>
#include <QtSerialPort/QSerialPort>

#include "CmdSink.h"
#include "ImgSink.h"

#include "ximage_handler.h"
#include "xsystem.h"
#include "xdevice.h"

#include "xcommand.h"
#include "xacquisition.h"
#include "xframe_transfer.h"
#include "xgig_factory.h"

class DetectorWorker : public QObject
{
	Q_OBJECT
public:
    explicit DetectorWorker(QObject* parent = nullptr);
    ~DetectorWorker();

    uint32_t get_frame_count();
    uint32_t get_lost_frame_count();
    bool get_is_save();
    std::string get_save_file_name();
    XImageHandler* get_ximage_handler();
    XEvent* get_xevent();
    void set_frame_count(uint32_t);
    void set_lost_frame_count(uint32_t);
    void set_is_save(bool);
    void set_save_file_name(std::string);

    void w_escrever_mensagem(const QString& caminhoArquivo, const QString& mensagem);
    void w_escrever_mensagem_t(const QString& caminhoArquivo, const QString& mensagem);

    std::atomic_bool stopRequested{ false };

private slots:
    void w_connect_detector(QString ip);
    void w_device_select(int index);
    void w_arduino_connect_serial_port();
    void w_binning_mode_change(int binning_mode);
    void w_gain_mode_change(int gain_mode);
    void w_integration_time_change(int integration_time);
    void w_recebido();

    void w_grab_start_operation(
        QString acquisition_mode, QString mechanical_mode, int interval_time, int image_quantity,
        QString file_path, QString file_prefix, time_t total_time);

    void w_grab_stop_operation();

    void w_escrever_inicio_log(
        const QString& caminho_arquivo, QString acquisition_mode, QString mechanical_mode, int interval_time, int image_quantity,
        QString file_path, QString file_prefix);
        
    bool w_arduino_check_open();
    void w_arduino_send_command(const std::string& comando);

    time_t w_calcular_tempo_restante(int img_total, int img_processadas, time_t starting_time);
    time_t w_calcular_tempo_total_esperado(int img_total, int integration_time, int interval_time, QString acquisition_mode);


signals:
    void message_box_error(QString title, QString message);
    void message_box_warning(QString title, QString message);
    void message_box_info(QString title, QString message);

    void device_conection_success(int num_devices);
    void device_select_success(
            QString d_ip, QString d_type, QString d_mac_address, QString d_firm_ver,
            QString d_cmd_port, QString d_img_port, QString d_serial_num);
    
    void integration_time_change_end(uint64_t frame_period);

    void enable_all();
    void disable_all();
    void update_tab(int index, int total_images, time_t starting_time, time_t remaining_time, QString file_path, QString file_prefix);

    void retornando();

private:
    CmdSink* cmd_sink = nullptr;
    ImgSink* img_sink = nullptr;
    XImageHandler ximg_handle;
    XEvent xevent;
    XGigFactory xfactory;
    XSystem* xsystem;
    XDevice* xdevice_ptr;
    XCommand xcommand;
    XFrameTransfer xtransfer;
    XAcquisition xacquisition;

    uint32_t lost_frame_count = 0; // Contagem de quadros perdidos
    uint32_t frame_count = 0; // Contagem de quadros
    bool is_save = true; // Flag para salvar

    std::string file_prefix;
    std::string file_path;
    std::string save_file_name;

    QSerialPort* serial;
    bool stop_bnt_pressed = false;
};