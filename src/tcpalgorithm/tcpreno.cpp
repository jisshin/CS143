#include "../../include/tcpalgorithm/tcpreno.hpp"
#include "../../include/common.hpp"
#include <iostream>

int TCPReno::getWindow(){
	return window_size;
}

void TCPReno::updateAck(int id){
	// End of fr/ft phase = receive a non duplicate ACK
	if ((fr_flag)&&(id == lost_id + 1)){
		window_size = fr_window;
	}

	// Normal operation
	if (window_size<threshold){
		window_size++;
	}
	else{
		window_size += 1/window_size;
	}
#ifdef DEBUG
	std::cout<<"Receive packet, window size = "<< window_size <<std::endl;
#endif
}

void TCPReno::updateLoss(int id){
	if(id!= lost_id){
		threshold = window_size/2;
		fr_window = window_size/2;
		window_size = window_size/2 + 3;
		lost_id = id;
		fr_flag = 1;
	}else{
		//fast recovery
		// if receive another duplicate ID
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
