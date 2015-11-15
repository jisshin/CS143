#ifndef _MSC_VER
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#else
#include "link.hpp"
#include "node.hpp"
#include "packet.hpp"
#endif

int Link::pushPacket(Packet* packet){
	if(max_buffer_size > cur_buffer_size){
		cur_buffer_size++;
		link_buffer.push(packet);
		return 1;
	}
	else{
		num_packet_drop++;
		return -1;
	}
}

Packet* Link::popPacket(){
	Packet* packet = link_buffer.front();
	link_buffer.pop();
	num_packet_thru++;
	return packet;
}

int Link::establishLink(Node* pointA, Node* pointB)
{
	A = pointA;
	B = pointB;
	return 1;
}

double Link::getDelay()
{
	double temp = PACKET_SIZE*BITS_PER_BYTE*cur_buffer_size;
	double queue_delay = temp/(link_rate*10^6);
	return queue_delay + link_delay;
}

Node* Link::get_other_node(Node* node)
{
	return (Node *)((uintptr_t)A ^ (uintptr_t)B ^ (uintptr_t)node);
}

int Link::weight()
{
	return 1;
}
