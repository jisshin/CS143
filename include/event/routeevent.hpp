#ifndef ROUTEEVENT_H
#define ROUTEEVENT_H

#include "../event.hpp"

class RouteEvent : public Event
{
  public:
    RouteEvent() : Event("ROUTE") {}

    int handleEvent()

}
#endif
