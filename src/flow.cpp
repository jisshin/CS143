#ifndef _MSC_VER
#include "../include/flow.hpp"
#include "../include/packet.hpp"
#else
#include "flow.hpp"
#include "packet.hpp"
#endif

#include <iostream>

Flow::Flow(std::string id, std::string src, std::string dest, int data_amt)\
: flow_id(id), \
  flow_src(src), \
  flow_dest(dest), \
  flow_data_amt(data_amt){

}

void Flow::update_flow(int id, int status){
	if (last_ack_id == id){
		dup_count++;
		if(dup_count == 3){
			// report a packet lost to TCP
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

Packet* Flow::genNextPacket(){
	//TODO: Assume fast recovery by default, may change in the future
	int window_size;
	if (dup_count >= 3){
		current_id = last_ack_id;
	}
	else{
		current_id++;
	}
	Packet* next_packet = new Packet(flow_id, flow_src, flow_dest, current_id);
	outstanding_count++;
	return next_packet;
}

int Flow::getAckID(int packet_id){
	if(packet_id == last_ack_id){
		last_ack_id++;
	}
	return last_ack_id;
}


double Flow::getTxDelay(double t){
	return TCP_strategy->getNextPacketTime();
}
