#include "ImgSink.h"
#include <iostream>
#include "DetectorWorker.h"

ImgSink::ImgSink(DetectorWorker* parent) : parent_(parent) {}

void ImgSink::OnXError(uint32_t err_id, const char* err_msg_)
{
	//std::cout << "Error ID: " << err_id << " Error Message: " << err_msg_ << std::endl;
	//QMessageBox::critical(parent_, "Erro " + err_id, err_msg_);
}

void ImgSink::OnXEvent(uint32_t event_id, uint32_t data)
{
	if (XEVENT_IMG_PARSE_DATA_LOST == event_id)
	{
		uint32_t lost_frame_count = this->parent_->get_lost_frame_count();

		this->parent_->set_lost_frame_count(lost_frame_count + data);
	}
}

void ImgSink::OnFrameReady(XImage* image_) 
{
	uint32_t lost_frame_count = this->parent_->get_lost_frame_count();
	bool is_save = this->parent_->get_is_save();
	XImageHandler* ximg_handle = this->parent_->get_ximage_handler();

	std::cout << "Frame ready" << std::endl;
	std::cout << "Width: " << image_->_width << std::endl;
	std::cout << "Height: " << image_->_height << std::endl;
	std::cout << "Lost line: " << lost_frame_count << std::endl;

	if (is_save)
	{
		ximg_handle->Write(image_);
	}
}

void ImgSink::OnFrameComplete()
{
	//verificando quais passos foram executados
	//this->parent_->w_escrever_mensagem("log.txt", "entrou no on frame complete\n");
	
	bool is_save = this->parent_->get_is_save();
	XImageHandler* ximg_handle = this->parent_->get_ximage_handler();
	std::string save_file_name = this->parent_->get_save_file_name();
	XEvent* frame_complete = this->parent_->get_xevent();

	std::cout << "Frame complete" << std::endl;

	if (is_save)
	{
		//this->parent_->w_escrever_mensagem("log.txt", "entrou no 'if (is_save)'\n");

		std::string txt_name = save_file_name.replace(save_file_name.find(".dat"), 4, ".txt");
		
		ximg_handle->SaveHeaderFile(txt_name.c_str());
		ximg_handle->CloseFile();

		this->parent_->set_is_save(false);
		is_save = 0;
	}

	frame_complete->Set();
	//this->parent_->w_escrever_mensagem("log.txt", "fim\n");
}