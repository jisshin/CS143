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
			// and reset to retransmit
			next_id = last_rx_ack_id;
			TCP_strategy->updateLoss(id);
		}else if(dup_count > 3){
			TCP_strategy->updateLoss(id);
		}

	}
	else{
		last_rx_ack_id = id;
		dup_count = 0;
		TCP_strategy->updateAck(id);
#ifdef DEBUG
		std::cout<<"receive src success "<< id - 1<<std::endl;
#endif
	}
	// Clear all timeout flags for both cases
	clearTimeout();
}

Packet* Flow::genNextPacketFromTx(){

	// if currently the window is full, don't generate new
	// packet
#ifdef DEBUG
	std::cout << "getting  src packet from TX " << std::endl;
#endif
	if (next_id > TCP_strategy->getWindow() + last_rx_ack_id){
			std::cout<<"window size " << TCP_strategy->getWindow() << std::endl;
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
	if((window_full_flag)&&(next_id <=  last_rx_ack_id + TCP_strategy->getWindow())){
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
	if (received_packet->packet_seq_id == last_tx_ack_id){
		last_tx_ack_id = received_packet->packet_seq_id + 1;
	}
	Packet* ack_packet = new Packet(flow_id, flow_dest,\
			flow_src, ACK_PACKET, last_tx_ack_id);
	std::cout<<"generate AckPacket with ID " << last_tx_ack_id << std::endl;
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
	if (RTT < min_RTT){
		min_RTT = RTT;
	}
}

double Flow::getAvgRTT(){
	if (RTT_count == 0){
		return 0;
	}else{
		return sum_RTT/RTT_count;
	}
}

void Flow::pushTimeout(int id){
	timeout_flags.push(id);
}

int Flow::checkTimeout(int id){
	int timeout = (timeout_flags.front() == id)?1:0;
	if(timeout == 1){
		clearTimeout();
		next_id = id;
	}
	return timeout;
}

void Flow::clearTimeout(){
	while (!timeout_flags.empty()){
		timeout_flags.pop();
	}
}
