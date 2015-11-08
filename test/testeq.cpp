/**
  * Checks the functionality of the event queue.
  */

#include "../include/eventqueue.hpp"

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
	
	//the order now should be 0.3/0.5/0.6
	assert(event.pop().time == 0.3);

	event4.time = 1;
	event5.time = 0.1;

	event.push(event4);
	event.push(event5);

	//the order should now be 0.1/0.5/0.6/1
	assert(event.pop().time == 0.1);
	assert(event.pop().time == 0.5);
	assert(event.pop().time == 0.6);
	assert(event.pop().time == 1);

	//if nothing is in the event, return "-1"
	assert(event.pop().time == -1); 
	assert(event.pop().time == -1);

	printf("Test Success - event queue\n");

	return EXIT_SUCCESS;
}