#ifndef RXENDEVENT_H
#define RXENDEVENT_H

#include "rxevent.hpp"

class Link;
class Node;

class RxEndEvent: public RxEvent
{
  RxEndEvent(Link* pLink, Node* pNode) : RxEvent(pLink, pNode);

  int handleEvent();
}

#endif
