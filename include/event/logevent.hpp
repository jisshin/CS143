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

	/**
	 * Event Handler for logging data from flow, link, node
	 * The next log event will be generated at next LOG_INTERVAL
	 */
    int handleEvent();

    // LOG_INTERVAL in sec
	static double LOG_INTERVAL;

  private:
    void logData(Link*);
    void logData(Flow*);
    void logData(Node*);

    /**
     * Accessor functions for network elements
     */
    double getBufOccupancy(Link*);
    int getPacketLoss(Link*);
    double getFlowRate(Link*);
    double getSentRate(Node* node);
    double getRcvdRate(Node* node);
    double getSentRate(Flow* flow);
    double getRcvdRate(Flow* flow);
    int getWindowSize(Flow* flow);
    double getPacketRTT(Flow* flow);

    // Convert number of byte received within a
    // LOG_INTERVAL to Mbps
	double byteToMbps(double);

};

#endif
