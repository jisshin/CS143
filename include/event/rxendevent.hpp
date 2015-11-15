#ifndef RXENDEVENT_H
#define RXENDEVENT_H

#include "rxevent.hpp"

class RxEndEvent: public RxEvent
{
public:
	RxEndEvent(Link* pLink, Node* pNode) : RxEvent(pLink, pNode) {}

	int handleEvent();
};

#endif
