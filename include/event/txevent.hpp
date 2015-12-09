#ifndef TXEVENT_H
#define TXEVENT_H

#include "../event.hpp"

#include <iostream>
#include <string>

/**
 * TxEvent implement Event. This is the interface class
 * for TxSrcEvent and other possible transmission events.
 */
class TxEvent :public Event {
public:
	TxEvent(double t, Packet* pPkt, Node* pNode) :
		tx_packet(pPkt), tx_node(pNode), Event(t)
	{}

	int handleEvent() { return 1; }

protected:
	Packet* tx_packet;
	Node* tx_node;

};

#endif //TXEVENT_H
