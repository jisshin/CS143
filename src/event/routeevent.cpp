#include "../include/networkmanager.hpp"
#include "../include/node.hpp"

int RouteEvent::handleEvent()
{
  NetworkManager* nm = NetworkManager::getInstance();

  Node* node = nm->resetNodeIterator();

  while(node != NULL)
  {
    node->updateRoute();
    node = nm->getNextNodeIterator();
  }

  //Add next event
}
