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
	NetworkManager* nm = NetworkManager::getInstance();
	Link* src_link = nm->getNode(flow_src)->lookupRouting(flow_dest);
	base_tx_delay = SRC_SIZE/src_link->link_rate;
}

void Flow::receive_ack(int id){
	if (last_ack_id == id){
		dup_count++;
		if(dup_count == 3){
			// report a packet lost to TCP
			// and set to retransmit
			next_id = last_ack_id;
			TCP_strategy->updateLoss(id);
		}
	}
	else{
		last_ack_id = id;
		dup_count = 0;
		outstanding_count--;
		TCP_strategy->updateAck(id);
	}
}

Packet* Flow::genNextPacketFromTx(){
	//TODO: Assume fast recovery by default, may change in the future

	// if currently the window is full, don't generate new
	// packet
	if (outstanding_count >= TCP_strategy->getWindow()){
			window_full_flag = 1;
			return NULL;
	}

	// send next packet, if window is not full, and have more
	// data to send
	else if(next_id < flow_data_amt){
		Packet* next_packet = new Packet(flow_id, flow_src, \
				flow_dest, next_id, SRC_PACKET);
		outstanding_count++;
		next_id++;
		return next_packet;
	}
	return NULL;
}

Packet* Flow::genNextPacketFromRx(){
	if((window_full_flag)&&(outstanding_count < TCP_strategy->getWindow())){
		window_full_flag = 0;
		Packet* next_packet = new Packet(flow_id, flow_src, \
				flow_dest, next_id, SRC_PACKET);
		outstanding_count++;
		next_id++;
		return next_packet;
	}
	return NULL;
}

//TODO: implement genAckPacket and get rid of getAckID

int Flow::getAckID(int packet_id){
	if(packet_id == last_ack_id){
		last_ack_id++;
	}
	return last_ack_id;
}

double Flow::getTxDelay()
{
	double delay = \
			((last_transmit_t + base_tx_delay) > EventQueue::cur_time)?\
					base_tx_delay:0;
	last_transmit_t = EventQueue::cur_time + delay;
	return delay;
}
