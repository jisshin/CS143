#ifndef TXSRCREVIVEEVENT_H
#define TXSRCREVIVEEVENT_H

#include "txevent.hpp"

class TxSrcReviveEvent : public TxEvent {
public:
	TxSrcReviveEvent(Packet* pPkt);

	int handleEvent();
};

#endif