#include "../include/eventqueue.hpp"
#include "../include/event/logevent.hpp"
#include "../include/event/routeevent.hpp"
#include "../include/common.hpp"

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
	initialize();

	while (registered_events.size() > 0)
	{
#ifdef JISOO
		int i;
		if (registered_events.size() < 10)
		{
			i = 1;
		}
#endif
		Event* e = registered_events.top();
		registered_events.pop();
		cur_time = e->time;
		e->handleEvent();
		delete e;
	}

	return 1;
}

void EventQueue::initialize()
{
	LogEvent* logEvent = new LogEvent(0);
	ResetEvent* resetEvent = new ResetEvent(0);
	push(logEvent);
	push(resetEvent);
}

int EventQueue::size(){
	return registered_events.size();
}

int EventQueue::empty(){
	return registered_events.empty();
}
