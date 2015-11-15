#ifndef EVENT_H
#define EVENT_H

/* C/C++ lib */
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

class Event{
	public:
		Event() {}

		virtual int handleEvent() { return 0; }

	protected:
		int commonTransmit();
		int commonIsSimOver();

		double time = -1;
};

/*
 * Function used by "eventqueue" to order each events. We will
 * prioritize events that happens faster. This comparator will
 * be used by eventqueue to order events correctly.
 */
struct CompareEvent
{
	bool operator()(const Event* lhs, const Event* rhs) const
	{
		return lhs->time > rhs->time;
	}
};
#endif //EVENT_H
