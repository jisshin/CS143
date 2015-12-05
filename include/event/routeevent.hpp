#ifndef ROUTEEVENT_H
#define ROUTEEVENT_H

#include "../event.hpp"
#include "../eventqueue.hpp"
#include "../common.hpp"


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
	static int network_complexity;

};

#endif
