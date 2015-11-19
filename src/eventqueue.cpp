#include "../include/eventqueue.hpp"
#include "../include/event/logevent.hpp"
#include "../include/event/routeevent.hpp"

double EventQueue::cur_time = 0;
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
		return (new Event());
	}

	//otherwise, return the event with highest priority.
	Event* e = registered_events.top();
	//and delete the event from the queue.
	registered_events.pop();
	return e;
}

int EventQueue::run()
{
	int route_event_counter = 0;

	LogEvent logEvent;
	RouteEvent routeEvent;

	while (registered_events.size() > 0)
	{
		Event* e = registered_events.top();
		registered_events.pop();
		cur_time = e->time;
		e->handleEvent();
		delete e;

		logEvent.time = cur_time;
		logEvent.handleEvent();

		if (cur_time / ROUT_INTERVAL == route_event_counter)
		{
			routeEvent.handleEvent();
			route_event_counter++;
		}
	}

	return 1;
}

int EventQueue::size(){
	return registered_events.size();
}

int EventQueue::empty(){
	return registered_events.empty();
}
