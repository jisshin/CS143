#ifndef RXENDEVENT_H
#define RXENDEVENT_H

#include "rxevent.hpp"

class RxEndEvent: public RxEvent
{
public:
	RxEndEvent(double t, Link* pLink, Node* pNode, Packet* pPkt)
		: RxEvent(t, pLink, pNode), rx_packet(pPkt)
	{}

	int handleEvent();

private:
	Packet* rx_packet;
};

#endif
