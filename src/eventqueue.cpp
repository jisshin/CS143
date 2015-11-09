#ifndef _MSC_VER
#include "../include/eventqueue.hpp"
#else
#include "eventqueue.hpp"
#endif

EventQueue* EventQueue::eventqueue = NULL;

EventQueue* EventQueue::getInstance()
{
	if (eventqueue) {
		return eventqueue;
	}
	else {
		return (eventqueue = new EventQueue());
	}
}

void EventQueue::push(Event* event)
{
	registered_events.push(event);
}

Event* EventQueue::pop()
{
	if (registered_events.size() == 0) {
		//if no event is there, then return default
		//event. 
		return (new Event(""));
	}

	//otherwise, return the event with highest priority.
	Event* e = registered_events.top();
	//and delete the event from the queue.
	registered_events.pop();
	return e;
}

int EventQueue::run()
{
	while (registered_events.size() > 0)
	{
		Event* e = registered_events.top();
		registered_events.pop();
		e->handleEvent();
	}

	return 1;
}

int EventQueue::empty(){
	return registered_events.empty();
}
