#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "../event.hpp"
#include "../eventqueue.hpp"
#include "../common.hpp"

class Link;
class Flow;
class Node;

class LogEvent : public Event
{
  public:
	LogEvent(double t) : Event(t)
	{
		EventQueue::getInstance()->num_non_core++;
	}

    int handleEvent();

  private:
    void logData(Link*);
    void logData(Flow*);
    void logData(Node*);

    double getBufOccupancy(Link*);
    int getPacketLoss(Link*);
    double getFlowRate(Link*);

    double getSentRate(Node* node);
    double getRcvdRate(Node* node);
    double getSentRate(Flow* flow);
    double getRcvdRate(Flow* flow);
    int getWindowSize(Flow* flow);
    double getPacketRTT(Flow* flow);

	double byteToMbps(double);
};

#endif
