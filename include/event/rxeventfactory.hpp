#ifndef RXEVENTFACTORY_H
#define RXEVENTFACTORY_H

#include "rxevent.hpp"

class RxEventFactory
{
public:
  RxEventFactory(){}

  RxEvent* makeRxEvent(Link*, Node*);
}
#endif
