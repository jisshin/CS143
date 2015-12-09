#ifndef RXROUTEEVENT_H
#define RXROUTEEVENT_H

#include "rxevent.hpp"

/**
 * RxRouteEvent implement RxEvent class. This event represent
 * the event when a routing packet is received.
 * Routing table will be updated in the handler.
 */
class RxRouteEvent : public RxEvent
{
public:
	RxRouteEvent(double t, Link* pLink, Node* pNode, Packet* pPkt);

	int handleEvent();

private:
	Packet* rx_packet;
};

#endif


