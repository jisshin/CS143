#ifndef _MSC_VER
#include "../include/flow.hpp"
#include "../include/packet.hpp"
#else
#include "flow.hpp"
#include "packet.hpp"
#endif

#include <iostream>




void Flow::update_flow(int id, int status){
	//TODO implement packet counter to record outstanding packet
	std::cout<<"packet"<<id<<"updated"<<std::endl;
	if (status == PACKET_RECEIVED){
		next_id++;
	}
}

Packet* Flow::genNextPacket(){
	//TODO next_packet id generate should based on TCP
	if(next_id == flow_data_amt){
		return NULL;
	}else{
		Packet* next_packet = new Packet(flow_id, flow_src, flow_dest, next_id);
		next_id++;
		return next_packet;
	}
}

int Flow::getAckID(int packet_id){
	if(packet_id == last_ack_id){
		last_ack_id++;
	}
	return last_ack_id;
}
