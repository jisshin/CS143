#include "../../include/event/routeevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/node.hpp"

int RouteEvent::handleEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();

	Node* node = nm->resetNodeIterator();
	std::vector<Node*> adj_nodes;
	
	while (node != NULL)
	{
		//send routing packet to every neighbor
		adj_nodes = node.getAdjNodes();
		for(std::vector<Node*>::size_type i = 0; i != adj_links.size(); i++) {
			Packet* route_pkt = new Packet("", *node, *adj_nodes[i], ROUT_PACKET);
			node->transmitPacket(route_pkt); 
		}
		node = nm->getNextNodeIterator();
	}

	if (!commonIsSimOver())
	{
		EventQueue* eq = EventQueue::getInstance();
		if(!eq.empty())
			eq->push(new RouteEvent(this->time + ROUT_INTERVAL));
	}

	return 1;
}
