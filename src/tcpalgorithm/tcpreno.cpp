#include "../../include/tcpalgorithm/tcpreno.hpp"
#include "../../include/common.hpp"
#include <iostream>

double TCPReno::getWindow(){
	return window_size;
}

void TCPReno::updateAck(int id){
	if (window_size<threshold){
		window_size++;
	}
	else{
		window_size += 1/window_size;
	}
	threshold = max_window/2;
    max_window = (window_size > max_window) ? window_size: max_window;
#ifdef DEBUG
	std::cout<<"Receive packet, window size = "<< window_size <<std::endl;
#endif
}

void TCPReno::updateLoss(int id){
	if(id!= lost_id){
		window_size = window_size/2;
		lost_id = id;
	}else{
		//fast recovery
		window_size++;
	}
#ifdef DEBUG
	std::cout<<"Lost packet, window size = "<< window_size<<std::endl;
#endif
}

void TCPReno::rx_timeout(){
	window_size = 1;
#ifdef DEBUG
	std::cout << "timeout!" << std::endl;
#endif
}
