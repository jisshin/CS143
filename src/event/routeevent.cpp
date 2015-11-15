#include "../../include/event/routeevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/node.hpp"

int RouteEvent::handleEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();

	Node* node = nm->resetNodeIterator();

	while (node != NULL)
	{
		node->updateRoute();
		node = nm->getNextNodeIterator();
	}

	if (!commonIsSimOver())
	{
		EventQueue* eq = EventQueue::getInstance();
		eq->push(new RouteEvent());
	}
}
