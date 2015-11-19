#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "../event.hpp"

class Link;
class Flow;
class Node;

const double LOG_TIME = 0.1;

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

    int getSentRate(Node* node);
    int getRcvdRate(Node* node);
    int getSentRate(Flow* flow);
    int getRcvdRate(Flow* flow);
    int getPacketRTT(Flow* flow);
};

#endif
