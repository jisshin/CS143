#ifndef TXEVENT_H
#define TXEVENT_H

#include "../event.hpp"

#include <iostream>
#include <string>
/* Forward declaration */
class Packet;

class TxEvent:public Event {
public:
	TxEvent::TxEvent(Packet* pPkt, Node* pNode):\
	tx_packet(pPkt),\
	tx_node(pNode)
	{

	}

	int handleEvent();

protected:
	Packet* tx_packet;
	Node* tx_node;

};

#endif //TXEVENT_H
