#ifndef ROUTEEVENT_H
#define ROUTEEVENT_H

#include "../event.hpp"

const double ROUT_INTERVAL = 1;
const double REST_INTERVAL = 5;

class RouteEvent : public Event
{
public:
	RouteEvent(double t) : Event(t) 
	{}

	int handleEvent();

};

class ResetEvent : public Event
{
public:
	ResetEvent(double t) : Event(t)
	{}

	int handleEvent();

};

#endif
