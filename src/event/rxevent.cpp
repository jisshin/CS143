#include "../../include/event/rxevent.hpp"
#include <iostream>

int RxEvent::handleEvent(){
	NetworkManager* nm = NetworkManager::getInstance();
	EventQueue* eventq = EventQueue::getInstance();
	Node* tx_node = nm->getNode(event_owner);

	if()

}

