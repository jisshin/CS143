#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "../event.hpp"

class Link;
class Flow;
class Node;

class LogEvent : public Event
{
  public:
    LogEvent() : Event() {}

    int handleEvent();

  private:
    void logData(Link*);
    void logData(Flow*);
    void logData(Node*);

    int getBufOccupancy(Link*);
    int getPacketLoss(Link*);
    int getFlowRate(Link*);
}
#endif
