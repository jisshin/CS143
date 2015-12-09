#ifndef RXACKEVENT_H
#define RXACKEVENT_H

#include "rxevent.hpp"

/**
 * RxAckEvent implement RxEvent class. It represents event when
 * the dest node receive a SRC packet and send back a ACK packet
 */
class RxAckEvent : public RxEvent
{
public:
	RxAckEvent(double t, Link* pLink, Node* pNode, Packet *pPkt)
		: RxEvent(t, pLink, pNode), rx_packet(pPkt)
	{}

	/**
	 * RxAckEvent will pop off the source event from link
	 * and send the appropriate ACK packet back to source.
	 */
	int handleEvent();

private:
	Packet* rx_packet;
};

#endif


