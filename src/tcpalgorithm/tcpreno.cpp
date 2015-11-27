#include "../../include/tcpalgorithm/tcpreno.hpp"
#include "../../include/common.hpp"
#include <iostream>



void TCPReno::updateAck(int id){
#ifdef JISOO
	int i = 0;
	if (id == 227)
	{
		i = 1;
	}
#endif
	// Receive duplicate ACK
	if (last_rx_ack_id == id){
		dup_count++;
		if(dup_count >= 3){
			packetLoss(id);
			
#ifdef CHECK_DROP
			std::cout << "packet lost" << std::endl;
#endif
		}
	}
	// Receive non duplicate ACK
	else{
		// end of fr phase
		if ((fr_flag)&&(id == last_rx_ack_id + 1)){
			window_size = fr_window;
			fr_flag = 0;
		}
		// Normal operation of increase window size
		if (window_size<threshold){
			window_size++;
		}
		else{
			window_size += 1/window_size;
		}
		last_rx_ack_id = id;
		dup_count = 1;
	}
}

void TCPReno::rx_timeout(int id){

	//we will be sending this id again in the future
	//invalid timeout
	if (id >= next_id) return;

	if(id > last_rx_ack_id){
		//window_size = 1;
		//next_id = last_rx_ack_id;
#ifdef CHECK_DROP
	std::cout << "timeout!" << std::endl;
#endif
	}
}

void TCPReno::packetLoss(int id){
	// Normal operation of increase window size

	if(dup_count == 3){
		// Reset window size and enter fr phase
		// and reset to retransmit
		fr_flag = 1;
		next_id = id;
		threshold = (window_size/2 > 2)? window_size/2 : 2;
		fr_window = (window_size/2 > 1)? window_size/2 : 1;
		window_size = window_size/2 + 3;

#ifdef JISOO
		//std::cout << id << ":" << threshold << std::endl;
#endif

	}else{
		// In fast recovery phase
		// if receive another duplicate ID
		window_size = (window_size+1 < 3*((double)fr_window)/2 -1) ?
				window_size + 1:3*((double)fr_window)/2 - 1;
		if (window_size < 1){
			window_size = 1;
		}
	}
}
