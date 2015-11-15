#ifndef _MSC_VER
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#else
#include "link.hpp"
#include "node.hpp"
#include "packet.hpp"
#endif

double Link::putPacket(){
	if(max_buffer_size > curr_buffer_size){
		curr_buffer_size++;
		return PACKET_SIZE*BITS_PER_BYTE*curr_buffer_size/(link_rate*10^6);
	}else{
		return -1;
	}
}

int Link::establishLink(Node* pointA, Node* pointB)
{
	A = pointA;
	B = pointB;
	return 1;
}

Node* Link::get_other_node(Node* node)
{
	return (Node *)((uintptr_t)A ^ (uintptr_t)B ^ (uintptr_t)node);
}

int Link::weight()
{
	return 1;
}