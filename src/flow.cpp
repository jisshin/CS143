#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#include "../include/eventqueue.hpp"
#include "../include/networkmanager.hpp"
#include "../include/common.hpp"

#include <iostream>

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
	TCP_strategy->updateAck(id);
	//clearTimeout();
}

Packet* Flow::genNextPacketFromTx(){

	// if currently the window is full, don't generate new
	// packet
#ifdef DEBUG
	std::cout << "getting  src packet from TX " << std::endl;
#endif
	if (TCP_strategy->windowFull()){
#ifdef DEBUG
			std::cout<<"window size " << TCP_strategy->getWindow() << std::endl;
			std::cout << "window full" << std::endl;
#endif
			window_full_flag = 1;
			return NULL;
	}

	// send next packet, if window is not full, and have more
	// data to send
#ifdef DEBUG
	std::cout<<"gen src packet from TX: "<< TCP_strategy->getNextID()<< std::endl;
#endif
	window_full_flag = 0;
	return comGenSrcPacket();
}

Packet* Flow::genNextPacketFromRx(){
	// if there's a newly open space in window
	if((window_full_flag)&&(!TCP_strategy->windowFull())){
		window_full_flag = 0;
#ifdef DEBUG
	std::cout<<"gen src packet from RX: "<< TCP_strategy->getNextID()<< std::endl;
#endif
		return comGenSrcPacket();
	}
	return NULL;
}


Packet* Flow::comGenSrcPacket() {
	if (flow_data_amt > 0) {
		Packet* next_packet = new Packet(flow_id, flow_src, \
			flow_dest, SRC_PACKET, TCP_strategy->getNextID());
		flow_data_amt -= next_packet->packet_size;
		TCP_strategy->updateTransmit();
		return next_packet;
	}
	std::cout << "data amount" << flow_data_amt << std::endl;
	return NULL;
}
//TODO: implement genAckPacket and get rid of getAckID
Packet* Flow::genAckPacket(Packet* received_packet)
{
	Packet* ack_packet = NULL;
	int new_ack_flag = 0;
	if (received_packet->packet_seq_id == last_tx_ack_id)
	{
		last_tx_ack_id++;
		new_ack_flag = 1;
	}

	if ((received_packet->packet_seq_id > last_tx_ack_id) || (new_ack_flag))
	{
		ack_packet = new Packet(flow_id, flow_dest, \
			flow_src, ACK_PACKET, last_tx_ack_id);
	}

#ifdef JISOO
	if (received_packet->packet_seq_id > last_tx_ack_id)
		std::cout << flow_id << " : " << received_packet->packet_seq_id << " " << last_tx_ack_id << std::endl;
#endif


	return ack_packet;
}

double Flow::getTxDelay()
{
	double delay = \
			((last_transmit_t + base_tx_delay) > EventQueue::cur_time)?\
					base_tx_delay:0;
	last_transmit_t = EventQueue::cur_time;
	return delay;
}

void Flow::recordRTT(double RTT){
	sum_RTT += RTT;
	RTT_count++;
	recent_RTT = RTT;
	if (RTT < min_RTT){
		min_RTT = RTT;
	}
}

double Flow::getAvgRTT(){
	if (RTT_count == 0){
		return 0.1;
	}else{
		return sum_RTT/RTT_count;
	}
}

int Flow::checkTimeout(int id){
	TCP_strategy->rx_timeout(id);
	return 0;
}

int Flow::getNumByteSent(){
	std::cout<<"check flow rate" << std::endl;
	int complete_packet = (packet_sent - 1 >= 0)?packet_sent - 1: 0;
	int total_sent = left_over_byte + \
			(complete_packet) * SRC_SIZE;
	// last packet is fully sent
	if (last_transmit_t + base_tx_delay < EventQueue::cur_time){
		total_sent += SRC_SIZE;
		left_over_byte = 0;
	}
	else{
		int fraction = SRC_SIZE* (EventQueue::cur_time - last_transmit_t)/base_tx_delay;
		total_sent += fraction;
		left_over_byte = SRC_SIZE - fraction;
	}
	packet_sent = 0;
	return total_sent;
}

void Flow::recordPacketSent(Packet* pkt){
	std::cout<<"send packet"<<std::endl;
	packet_sent++;
}
