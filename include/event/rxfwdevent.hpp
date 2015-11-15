#ifndef RXFWDEVENT_H
#define RXFWDEVENT_H

#include "rxevent.hpp"

class Link;
class Node;

class RxFwdEvent: public RxEvent
{
  RxFwdEvent(Link* pLink, Node* pNode) : RxEvent(pLink, pNode);

  int handleEvent();
}

#endif
