#include "../include/eventqueue.hpp"

#include <vector>
#include <map>

void EventQueue::enqueue(double time, Event event)
{
	std::map<double, std::vector<Event>>::iterator iter;
	iter = registered_events.find(time);

	if (iter != registered_events.end())
	{
		std::vector<Event> e;
		e.push_back(event);	
		registered_events[time] = e;
	}
	else
	{
		registered_events[time].push_back(event);
	}

}

Event EventQueue::dequeue()
{
	std::map<double, std::vector<Event>>::iterator iter;
	iter = registered_events.begin();

	Event event = (iter->second()).pop_back();

	if (e.size() == 0)
	{
		registered_events.erase(iter);
	}

	return event;
}