#include "../include/node.hpp"
#include "../include/link.hpp"
#include "../include/packet.hpp"
#include "../include/networkmanager.hpp"

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

	return routing_table[dest].first;
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
#ifdef ROUTING_TEST

	if(packet->packet_type == ROUT_PACKET && packet->packet_dest == *this)
		routePacket(packt);

	return 1;
#else
	return 0;
#endif //ROUTIING_TEST

}

void routePacket(Packet* pkt)
{
#ifdef ROUTING_TEST
	//get routing table of source packet--simulates packet with routing table info
	NetworkManager* nm = NetworkManager::getInstance();
	Node* nbr = nm->getNode(pkt->packet_src);
	Link* link_to_nbr = nm->getLinkBtwNodes(pkt->packet_src, *this);
	int nbr_link_wt = link_to_nbr->weight();

	routing_table_t nbr_route = nbr->getRoutingTable();
	//Loop through neighbor's routing table to update this routing table
	for(routing_table_t::iterator it = nbr_route.begin(); it != nbr_route.end(); ++it)
	{
		std::string dest = it->first;
		int nbr_to_dest = it->second.second;
		//look for the destination id in this routing table
		std::unordered_map<std::string, std::pair<Link*, int> >::const_iterator got = this_routing_table.find(dest);

		//destination is not found
		if( got == this_routing_table.end() )
		{
			//current distance is distance to nbr + distance in nbr's routing table
			std::pair<Link*, int> route_entry (link_to_nbr, nbr_link_wt + nbr_to_dest);
			this_routing_table.insert({{dest, route_entry}});
		}

		//destination is found but the new path is better
		else if( got->second.second > wt + dist )
		{
			//update current distance
			std::pair<Link*, int> route_entry (link_to_nbr, wt + dist);
			this_routing_table.erase(got);
			this_routing_table.insert({{dest, route_entry}});
		}
	}
#endif
}

std::vector<Node*> Node::getAdjNodes(){
	std::vector<Node*> adj_nodes (adj_links.size());
	for(std::vector<int>::size_type i = 0; i != adj_nodes.size(); i++) {
		adj_nodes.push_back( adj_links[i]->get_other_node(this) );
	}
	return adj_nodes;
}

routing_table_t Node::getRoutingTable(){
	return routing_table;
}

void Node::establishLink(Link* link)
{
	adj_links.push_back(link);
}
