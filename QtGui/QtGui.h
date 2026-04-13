#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <winsock2.h>
#include <windows.h>

#include <QtWidgets/QMainWindow>
#include <QObject>
#include "ui_QtGui.h"

#include "CmdSink.h"
#include "ImgSink.h"
#include "ximage_handler.h"
#include "xsystem.h"
#include "xdevice.h"
#include "xcommand.h"
#include "xacquisition.h"
#include "xframe_transfer.h"
#include "xgig_factory.h"

class QtGui : public QMainWindow
{
    Q_OBJECT

public:
    QtGui(QWidget *parent = nullptr);
    ~QtGui();
    QString get_file_name();
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
    HANDLE abrirPortaSerial(const char*);
    void enviarComando(HANDLE, const std::string& );

private slots:
	void on_connect_btn_clicked();
    void on_device_select_changed(int);
    void on_device_info_update_btn_clicked();

    void on_acquisition_mode_changed(int);
    void on_mechanical_mode_changed(int);
    void on_binning_mode_changed(int);
    void on_gain_mode_changed(int);
    void on_integration_time_changed();
    void on_interval_time_changed();
    void on_image_quantity_combobox_changed(int);
    void on_image_quantity_input_changed();
    void on_file_prefix_input_changed();

    int  get_total_approximate_time();
    void set_total_approximate_time();

    void on_choose_file_path_btn_clicked();
    void on_grab_btn_clicked();
	void on_stop_grab_btn_clicked();

    void update_progress_tab(int, int, int, std::string);
    void update_displayed_image(int);

private:
    Ui::QtGuiClass ui;
    CmdSink* cmd_sink;
	ImgSink* img_sink;
    XImageHandler ximg_handle;
	XEvent xevent;
    XGigFactory xfactory;
    XSystem* xsystem;
    XDevice* xdevice_ptr;
    XCommand xcommand;
    XFrameTransfer xtransfer;
    XAcquisition xacquisition;
	QString file_name;
    uint32_t lost_frame_count; // Contagem de quadros perdidos
    uint32_t frame_count; // Contagem de quadros
    bool is_save; // Flag para salvar
    std::string save_file_name; // Nome do arquivo para salvar
    HANDLE hserial;
};
