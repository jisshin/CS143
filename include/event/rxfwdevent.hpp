#ifndef RXFWDEVENT_H
#define RXFWDEVENT_H

#include "rxevent.hpp"

class RxFwdEvent : public RxEvent
{
public:
	RxFwdEvent(double t, Link* pLink, Node* pNode, Packet *pPkt) 
		: RxEvent(t, pLink, pNode), rx_packet(pPkt)
	{}

	int handleEvent();

private:
	Packet* rx_packet;
};

#endif
