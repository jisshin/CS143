#ifndef ROUTEEVENT_H
#define ROUTEEVENT_H

#include "../event.hpp"

const int ROUT_INTERVAL = 100;
const int ROUT_RESET_INTERVAL = 1000;

class RouteEvent : public Event
{
public:
	RouteEvent() : Event() {}

	int handleEvent();

private:
	void resetEvent();
	void routeEvent();
	static int counter;

};

#endif
