#ifndef ROUTEEVENT_H
#define ROUTEEVENT_H

#include "../event.hpp"

const int ROUT_INTERVAL = 100;

class RouteEvent : public Event
{
  public:
    RouteEvent() : Event() {}

	int handleEvent();

};

#endif
