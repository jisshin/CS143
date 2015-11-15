#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "../event.hpp"

class LogEvent : public Event
{
  public:
    LogEvent() : Event("LOG") {}

    int handleEvent();

  private:
    logData(Link*);
    logData(Flow*);
    logData(Node*);

    int getBufOccupancy(Link*);
    int getPacketLoss(Link*);
}
#endif
