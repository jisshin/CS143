#ifndef RXFWDEVENT_H
#define RXFWDEVENT_H

#include "rxevent.hpp"

class RxFwdEvent : public RxEvent
{
public:
	RxFwdEvent(Link* pLink, Node* pNode) : RxEvent(pLink, pNode) {}

	int handleEvent();
};

#endif
