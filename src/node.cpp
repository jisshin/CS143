#include "../include/node.hpp"
#include "../include/link.hpp"
#include "../include/packet.hpp"

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

	Link* link = lookupRouting(tx_packet->packet_dest);

	//there is no tx_link with such tx_link_id that is adjacent
	//to node. this shouldn't happen.
	if (link == NULL) return -2;

	int result = link->pushPacket(tx_packet);

	return result;
}

int Node::receivePacket(Packet*)
{
	return 1;
}

void Node::updateRoute(){
	routing_table_t this_routing_table = this->getRoutingTable();

	for(std::vector<Link*>::size_type i = 0; i != adj_links.size(); i++) {
		Node* nbr = adj_links[i]->get_other_node(this);
		//TODO: send request routing table packet out to nbr to get nbr routing table
		
		routing_table_t nbr_routing_table;
		//nbr_routing_table = adj_nodes[i]->getRoutingTable();
		//hi kevin. above line doesn't compile, and didn't look like a trivial
		//problem. so i will leave it to you. so i commented it out.

		//Get link weight.
		int wt = adj_links[i]->weight();

		//Loop through neighbor's routing table to update this routing table
		for(routing_table_t::iterator it = nbr_routing_table.begin(); it != nbr_routing_table.end(); ++it)
		{
			std::string id = it->first;
			int dist = it->second.second;

			//look for the id in this routing table
			std::unordered_map<std::string, std::pair<Link*, int> >::const_iterator got = this_routing_table.find(id);

			//id is not found
			if( got == this_routing_table.end() )
			{
				//current distance is distance to nbr + distance in nbr's routing table
				std::pair<Link*, int> link_entry (adj_links[i], wt + dist);
				std::pair<std::string, std::pair<Link*, int> > new_entry (id, link_entry);
				this_routing_table.insert(new_entry);
			}

			//id is found but the new path is better
			else if( got->second.second > wt + dist )
			{
				//update current distance
				std::pair<Link*, int> link_entry (adj_links[i], wt + dist);
				std::pair<std::string, std::pair<Link*, int> > new_entry (id, link_entry);
				this_routing_table.erase(got);
				this_routing_table.insert(new_entry);
			}
		}
	}
}

std::vector<Node*> Node::getAdjNodes()
{
	return std::vector<Node*>();
}

routing_table_t Node::getRoutingTable(){
	return routing_table;
}

void Node::establishLink(Link* link)
{
	adj_links.push_back(link);
}
