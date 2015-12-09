#ifndef ROUTEEVENT_H
#define ROUTEEVENT_H

#include "../event.hpp"
#include "../eventqueue.hpp"
#include "../common.hpp"

/**
 * RouteEvent implement Event class. RouteEvent should
 * be generated from ResetEvent
 */
class RouteEvent : public Event
{
public:
	RouteEvent(double t) : Event(t) 
	{
		EventQueue::getInstance()->num_non_core++;
	}

	/**
	 * Route event handler. Send out routing packet to update routing table
	 * for each node.
	 */
	int handleEvent();


};

/**
 * ResetEvent implement Event class. ResetEvent will
 * self generate every REST_INTERVAL sec
 */
class ResetEvent : public Event
{
public:
	ResetEvent(double t) : Event(t)
	{
		EventQueue::getInstance()->num_non_core++;
	}

	/**
	 * Generate routing event to reset routing table
	 * for each node.
	 */
	int handleEvent();

	// This variable describe the number of routing
	// packet for each ResetEvent
	static int network_complexity;

};

#endif
