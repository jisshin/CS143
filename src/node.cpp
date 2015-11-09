#ifndef _MSC_VER
#include "../include/node.hpp"
#include "../include/link.hpp"
#include "../include/packet.hpp"
#else
#include "node.hpp"
#include "link.hpp"
#include "packet.hpp"
#endif

#include <stdint.h>
#include <iostream>
Link* Node::lookupRouting(std::string dest){
	//if the size of the adj_links is one, the node acts like
	//a host. it does not do "dynamic routing".

	//should not happen
	if (adj_links.size() < 1)
		return NULL;

	if (adj_links.size() == 1)
		return adj_links[0];

	return routing_table[dest];
}

double Node::transmitPacket(Packet* tx_packet, uintptr_t* rx_node){

	Link* tx_link = lookupRouting(tx_packet->packet_dest);
	*rx_node = (uintptr_t)tx_link->get_other_node(this);

	//there is no tx_link with such tx_link_id that is adjacent
	//to node. this shouldn't happen.
	if (tx_link == NULL) return -2;

	double queue_delay = tx_link->putPacket();

	if (queue_delay < 0){
		// packet is dropped due to a full link buffer
		return -1;
	}

	return queue_delay + tx_link->getDelay();
}

void Node::establishLink(Link* link)
{
	adj_links.push_back(link);
}
