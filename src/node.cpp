#ifndef _MSC_VER
#include "../include/node.hpp"
#include "../include/link.hpp"
#include "../include/packet.hpp"
#else
#include "node.hpp"
#include "link.hpp"
#include "packet.hpp"
#endif

std::string Node::lookupRouting(std::string dest){
	//if the size of the adj_links is one, the node acts like
	//a host. it does not do "dynamic routing".
	if (adj_links.size() == 1)
		return (std::string) *adj_links[0];

	return routing_table[dest];
}

double Node::transmitPacket(Packet* tx_packet){

	std::string tx_link_id = lookupRouting(tx_packet->packet_dest);

	Link* tx_link = NULL;

	for (int i = 0; i < adj_links.size(); i++)
	{
		if (tx_link_id == (std::string) *(adj_links[i]))
		{
			tx_link = adj_links[i];
			break;
		}
	}

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