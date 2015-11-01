#include "../include/eventqueue.hpp"


void EventQueue::push(Event event)
{
	registered_events.push(event);
}

Event EventQueue::pop()
{
	if (registered_events.size() == 0) {
		return Event();
	}

	Event e = registered_events.top();
	registered_events.pop();
	return e;
}