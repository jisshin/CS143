#include "../../include/event/routeevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"

int ResetEvent::network_complexity = 0;
int ResetEvent::handleEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();
	EventQueue *eq = EventQueue::getInstance();
	eq->num_non_core--;

	Node* node = nm->resetNodeIterator();
	std::vector<Node*> adj_nodes;

	while (node != NULL)
	{
		node->resetRouting();
		node = nm->getNextNodeIterator();
	}

	if (eq->size() - eq->num_non_core > 0)
	{

		RouteEvent *e = NULL;
		for (int i = 0; i < network_complexity; i++){
			e = new RouteEvent(time + ROUT_INTERVAL);
		}
	}

#ifdef JISOO
	std::cout << "Routing Reset" << std::endl;
#endif
	return 1;
}

int RouteEvent::handleEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();
	EventQueue* eq = EventQueue::getInstance();
	eq->num_non_core--;
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

	return 1;
}
