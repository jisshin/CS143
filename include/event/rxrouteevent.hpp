#ifndef RXROUTEEVENT_H
#define RXROUTEEVENT_H

#include "rxevent.hpp"

class RxRouteEvent : public RxEvent
{
public:
	RxRouteEvent(Link* pLink, Node* pNode) : RxEvent(pLink, pNode) {}

	int handleEvent();
};

#endif


