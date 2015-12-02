#ifndef RXACKEVENT_H
#define RXACKEVENT_H

#include "rxevent.hpp"

class RxAckEvent : public RxEvent
{
public:
	RxAckEvent(double t, Link* pLink, Node* pNode, Packet *pPkt)
		: RxEvent(t, pLink, pNode), rx_packet(pPkt)
	{}


	int handleEvent();

private:
	Packet* rx_packet;
};

#endif


