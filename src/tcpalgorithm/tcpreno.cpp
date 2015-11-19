#include "../../include/tcpalgorithm/tcpreno.hpp"
#include "../../include/common.hpp"
#include <iostream>

double TCPReno::getWindow(){
	return window_size;
}

void TCPReno::updateAck(int id){
	window_size += 1/window_size;
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
