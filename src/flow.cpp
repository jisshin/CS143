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
}

Packet* Flow::genNextPacket(){
	//TODO next_packet id generate should based on TCP
	Packet* next_packet = new Packet(flow_src, flow_dest, next_id, this);
	next_id++;
	return next_packet;
}
