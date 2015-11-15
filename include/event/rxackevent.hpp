#ifndef RXACKEVENT_H
#define RXACKEVENT_H

#include "rxevent.hpp"

class Link;
class Node;

class RxAckEvent: public RxEvent
{
  RxAckEvent(Link* pLink, Node* pNode) : RxEvent(pLink, pNode);

  int handleEvent();
}

#endif
