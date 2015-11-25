#include "../include/node.hpp"
#include "../include/link.hpp"
#include "../include/packet.hpp"

#include <stdint.h>
#include <iostream>
#include <limits>

Link* Node::lookupRouting(std::string dest){

	if (routing_table.count(dest) == 0)
		return NULL;

	return routing_table[dest];

}

int Node::transmitPacket(Packet* tx_packet){

	packet_sent += tx_packet->packet_size;
	Link* link = lookupRouting(tx_packet->packet_dest);

	//there is no tx_link with such tx_link_id that is adjacent
	//to node. this shouldn't happen.
	if (link == NULL) return -2;

	int result = link->pushPacket(tx_packet);

	return result;
}

int Node::receivePacket(Packet* packet)
{
	packet_rcvd += packet->packet_size;

	return 1;
}

void Node::resetRouting()
{
	routing_table_helper_t::iterator iter;

	for (iter = routing_helper_table.begin(); iter != routing_helper_table.end(); iter++)
	{
		iter->second = std::numeric_limits<double>::max();
	}

}

void Node::routePacket(Node* nbr, Link* link_to_nbr)
{
	int nbr_link_wt = link_to_nbr->getDelay();
	routing_table_t nbr_route = nbr->routing_table;
	routing_table_helper_t nbr_helper_route = nbr->routing_helper_table;

	//Loop through neighbor's routing table to update this routing table
	for(routing_table_t::iterator it = nbr_route.begin(); it != nbr_route.end(); ++it)
	{
		std::string dest = it->first;
		int nbr_to_dest = nbr_helper_route[dest];

		if (dest == node_id) continue; //if destination is itself, ignore it

		if( routing_table.count(dest) == 0 ||
			//destination is not found
			routing_helper_table[dest] > nbr_link_wt + nbr_to_dest)
			//destination is found but the new path is better
		{
			//current distance is distance to nbr + distance in nbr's routing table
			routing_table[dest] = link_to_nbr;
			routing_helper_table[dest] = nbr_link_wt + nbr_to_dest;
		}

	}
}

std::vector<Node*> Node::getAdjNodes(){
	std::vector<Node*> adj_nodes;
	for(int i = 0; i < adj_links.size(); i++) {
		adj_nodes.push_back( adj_links[i]->get_other_node(this) );
	}
	return adj_nodes;
}


void Node::establishLink(Link* link)
{
	std::string nbr = *(link->get_other_node(this));
	routing_table[nbr] = link;
	routing_helper_table[nbr] = link->getDelay();
	adj_links.push_back(link);
}
