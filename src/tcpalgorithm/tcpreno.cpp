#include "../../include/tcpalgorithm/tcpreno.hpp"


int TCPReno::getWindow(){
	return window_size;
}

void TCPReno::updateAck(int id){
	window_size++;
}

void TCPReno::updateLoss(int id){
	window_size = window_size/2;
}
