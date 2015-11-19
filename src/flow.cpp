#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#include "../include/eventqueue.hpp"
#include "../include/networkmanager.hpp"

#include <iostream>
#include <cassert>

Flow::Flow(std::string id, std::string src, std::string dest, int data_amt)\
: flow_id(id), \
  flow_src(src), \
  flow_dest(dest), \
  flow_data_amt(data_amt){
}

void Flow::setTxDelay(double link_rate){
	std::cout << "link rate" << link_rate<<std::endl;
	base_tx_delay = SRC_SIZE/link_rate;
	std::cout<<"tx delay"<< base_tx_delay << std::endl;
}

void Flow::receive_ack(int id){
	if (last_rx_ack_id == id){
		dup_count++;
		if(dup_count == 3){
			// report a packet lost to TCP
			// and set to retransmit
			next_id = last_rx_ack_id;
			TCP_strategy->updateLoss(id);
		}
	}
	else{
		last_rx_ack_id = id;
		dup_count = 0;
		outstanding_count--;
		TCP_strategy->updateAck(id);
#ifdef DEBUG
		std::cout<<"receive src success "<< id<<std::endl;
#endif
	}
}

Packet* Flow::genNextPacketFromTx(){
	//TODO: Assume fast recovery by default, may change in the future

	// if currently the window is full, don't generate new
	// packet
	if (outstanding_count >= TCP_strategy->getWindow()){
			window_full_flag = 1;
			std::cout<<"window full" << std::endl;
			return NULL;
	}

	// send next packet, if window is not full, and have more
	// data to send
#ifdef DEBUG
	std::cout<<"gen src packet from TX: "<< next_id << std::endl;
#endif
	window_full_flag = 0;
	return comGenSrcPacket();
}

Packet* Flow::genNextPacketFromRx(){
	// if there's a newly open space in window
	if((window_full_flag)&&(outstanding_count < TCP_strategy->getWindow())){
		window_full_flag = 0;
		std::cout<<"gen src packet from RX "<< next_id<<std::endl;
		return comGenSrcPacket();
	}
	return NULL;
}

Packet* Flow::comGenSrcPacket(){
	if(flow_data_amt > 0){
			Packet* next_packet = new Packet(flow_id, flow_src, \
					flow_dest, SRC_PACKET, next_id);
			outstanding_count++;
			flow_data_amt -= next_packet->packet_size;
			next_id++;
			return next_packet;
	}
	std::cout<<"data amount"<< flow_data_amt << std::endl;
	return NULL;
}



//TODO: implement genAckPacket and get rid of getAckID
Packet* Flow::genAckPacket(Packet* received_packet)
{
	if (last_tx_ack_id == -1){
		last_tx_ack_id = received_packet->packet_seq_id;
	}
	if (received_packet->packet_seq_id == last_tx_ack_id){
		last_tx_ack_id++;
	}
	Packet* ack_packet = new Packet(flow_id, flow_dest,\
			flow_dest, ACK_PACKET, last_tx_ack_id);
	return ack_packet;
}

double Flow::getTxDelay()
{
	double delay = \
			((last_transmit_t + base_tx_delay) > EventQueue::cur_time)?\
					base_tx_delay:0;
	last_transmit_t = EventQueue::cur_time + delay;
	return delay;
}
