#ifndef RXENDEVENT_H
#define RXENDEVENT_H

#include "rxevent.hpp"

/**
 * RxEndEvent implement RxEvent class. It represents event
 * when a ACK packet is received at source.
 */
class RxEndEvent: public RxEvent
{
public:
	RxEndEvent(double t, Link* pLink, Node* pNode, Packet* pPkt)
		: RxEvent(t, pLink, pNode), rx_packet(pPkt)
	{}

	/**
	 * RxEndEvent handler pop the ACK packet off from link and
	 * update flow with the ACK packet info.
	 */
	int handleEvent();

private:
	Packet* rx_packet;
};

#endif
