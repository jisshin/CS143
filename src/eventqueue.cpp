#include "../include/eventqueue.hpp"


void EventQueue::push(Event event)
{
	registered_events.push(event);
}

Event EventQueue::pop()
{
	/*
	if (registered_events.size() == 0) {
		//if no event is there, then return default
		//event. 
		return Event();
	}*/

	//otherwise, return the event with highest priority.
	Event e = registered_events.top();
	//and delete the event from the queue.
	registered_events.pop();
	return e;
}

int EventQueue::empty(){
	return registered_events.empty();
}
