#ifndef RXROUTEEVENT_H
#define RXROUTEEVENT_H

#include "rxevent.hpp"

class RxRouteEvent : public RxEvent
{
public:
	RxRouteEvent(Link* pLink, Node* pNode, Packet* pPkt) 
		: RxEvent(pLink, pNode), rx_packet(pPkt) {}

	int handleEvent();

private:
	Packet* rx_packet;
};

#endif


