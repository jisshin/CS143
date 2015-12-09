#ifndef TXSRCEVENT_H
#define TXSRCEVENT_H

#include "txevent.hpp"

/**
 * TxSrcEvent implement TxEvent. This represent the event
 * where a SRC packet is transmitted from source node.
 */
class TxSrcEvent : public TxEvent {
public:
	TxSrcEvent(double time, Packet* pPkt);

	int handleEvent();
};

#endif
