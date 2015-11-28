#ifndef ROUTEEVENT_H
#define ROUTEEVENT_H

#include "../event.hpp"
#include "../eventqueue.hpp"
	
const double ROUT_INTERVAL = 0.000001;
const double REST_INTERVAL = 5;

class RouteEvent : public Event
{
public:
	RouteEvent(double t) : Event(t) 
	{
		EventQueue::getInstance()->num_non_core++;
	}

	int handleEvent();

};

class ResetEvent : public Event
{
public:
	ResetEvent(double t) : Event(t)
	{
		EventQueue::getInstance()->num_non_core++;
	}

	int handleEvent();

};

#endif
