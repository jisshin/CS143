#ifndef RXEVENTFACTORY_H
#define RXEVENTFACTORY_H

#include "rxevent.hpp"

class Link;
class Node;

/**
 * RxEventFactory class generate an RxEvent based on the
 * type of the packet.
 * If a packet hasn't reach each destination, an RxFwd event
 * will be generated.
 * Else, RxEnd/RxAck/RxRoute event will be generated based
 * on the packet type.
 */
class RxEventFactory
{
public:
  RxEventFactory(){}

  RxEvent* makeRxEvent(double time, Link*, Node*, Packet*);
};

#endif
