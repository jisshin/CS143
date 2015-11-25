#ifndef RXENDEVENT_H
#define RXENDEVENT_H

#include "rxevent.hpp"

class RxEndEvent: public RxEvent
{
public:
	RxEndEvent(Link* pLink, Node* pNode, Packet* pPkt)
		: RxEvent(pLink, pNode), rx_packet(pPkt)
	{}

	int handleEvent();

private:
	Packet* rx_packet;
};

#endif
