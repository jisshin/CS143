#include "eventqueue.hpp"

#include <cassert>
#include <cstdlib>

int main()
{
	EventQueue event = EventQueue::get_instance();
	Event event1, event2, event3, event4, event5;
	
	event1.time = 0.5;
	event2.time = 0.6;
	event3.time = 0.3;

	event.push(event1);
	event.push(event2);
	event.push(event3);
	
	Event e = event.pop();
	assert(e.time == 0.3);

	event4.time = 1;
	event5.time = 0.1;

	event.push(event4);
	event.push(event5);

	assert(event.pop().time == 0.1);
	assert(event.pop().time == 0.5);
	assert(event.pop().time == 0.6);
	assert(event.pop().time == 1);

	assert(event.pop().time == -1);
	assert(event.pop().time == -1);
	return EXIT_SUCCESS;
}