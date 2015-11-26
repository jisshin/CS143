#include "../include/tcpalgorithm.hpp"

int TCPAlgorithm::windowFull(){
	return (next_id > window_size + last_rx_ack_id);
}

void TCPAlgorithm::updateTransmit(){
	next_id++;
}

