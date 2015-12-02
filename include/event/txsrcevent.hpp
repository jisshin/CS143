#ifndef TXSRCEVENT_H
#define TXSRCEVENT_H

#include "txevent.hpp"

class TxSrcEvent : public TxEvent {
public:
	TxSrcEvent(double time, Packet* pPkt);

	int handleEvent();
};

#endif
