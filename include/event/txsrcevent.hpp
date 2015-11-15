#ifndef TXSRCEVENT_H
#define TXSRCEVENT_H

#include "txevent.h"

//
class TxSrcEvent: public TxEvent {
public:
  TxSrcEvent(Packet* pPkt);

  int handleEvent();
}
#endif
