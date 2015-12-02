#ifndef RXROUTEEVENT_H
#define RXROUTEEVENT_H

#include "rxevent.hpp"

class RxRouteEvent : public RxEvent
{
public:
	RxRouteEvent(double t, Link* pLink, Node* pNode, Packet* pPkt);

	int handleEvent();

private:
	Packet* rx_packet;
};

#endif


