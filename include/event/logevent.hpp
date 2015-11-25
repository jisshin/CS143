#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "../event.hpp"

class Link;
class Flow;
class Node;

const double LOG_INTERVAL = 0.01;

class LogEvent : public Event
{
  public:
    LogEvent(double t) : Event(t) {}

    int handleEvent();

  private:
    void logData(Link*);
    void logData(Flow*);
    void logData(Node*);

    double getBufOccupancy(Link*);
    int getPacketLoss(Link*);
    int getFlowRate(Link*);

    int getSentRate(Node* node);
    int getRcvdRate(Node* node);
    int getSentRate(Flow* flow);
    int getRcvdRate(Flow* flow);
    int getWindowSize(Flow* flow);
    double getPacketRTT(Flow* flow);
};

#endif
