#include "../../include/event/routeevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"

int RouteEvent::counter = 0;

int RouteEvent::handleEvent()
{
	if (counter % (ROUT_RESET_INTERVAL / ROUT_INTERVAL) == 0)
	{
		resetEvent();
		routeEvent();
	}
	else
	{
		routeEvent();
	}

	counter++;

	return 1;
}

void RouteEvent::resetEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();

	Node* node = nm->resetNodeIterator();
	std::vector<Node*> adj_nodes;

	while (node != NULL)
	{
		node->resetRouting();
		node = nm->getNextNodeIterator();
	}
}

void RouteEvent::routeEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();

	Node* node = nm->resetNodeIterator();
	std::vector<Node*> adj_nodes;
	
	while (node != NULL)
	{
		//send routing packet to every neighbor
		adj_nodes = node->getAdjNodes();
		for(std::vector<Node*>::size_type i = 0; i != adj_nodes.size(); i++) 
		{
			Packet* route_pkt = new Packet("", *node, *adj_nodes[i], ROUT_PACKET);
			commonTransmit(node, route_pkt);
		}
		node = nm->getNextNodeIterator();
	}
}
