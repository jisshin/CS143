#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"

double Link::putPacket(){
	if(max_buffer_size > curr_buffer_size){
		curr_buffer_size++;
		return Packet::packet_size*BITS_PER_BYTE*curr_buffer_size/(link_rate*10^6);
	}else{
		return -1;
	}
}
