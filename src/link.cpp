#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"

int Link::pushPacket(Packet* packet){
	if(max_buf_size_in_byte > cur_buf_size_in_byte){
		cur_buf_size_in_byte += packet->packet_size;
		link_buffer.push(packet);
		return 1;
	}
	else{
		num_packet_drop++;
		return -1;
	}
}

Packet* Link::peekPacket()
{
	return link_buffer.front();
}

Packet* Link::lastPacket()
{
	return link_buffer.back();
}

Packet* Link::popPacket(){
	Packet* packet = link_buffer.front();
	link_buffer.pop();
	packet_thru += packet->packet_size;
	cur_buf_size_in_byte -= packet->packet_size;
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
	double temp = cur_buf_size_in_byte*BITS_PER_BYTE;
	double queue_delay = temp/(link_rate);
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

