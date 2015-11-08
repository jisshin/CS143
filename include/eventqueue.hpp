#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

/* C/C++ lib */
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>

/* other lib */
#include "event.hpp"

class EventQueue{
	public:
		static EventQueue& get_instance(){
			static EventQueue instance; 
			return instance; 	
		}
		
		void push(Event event);
		Event pop();
		int empty();

	private:
		EventQueue(){};
		
		std::priority_queue<Event, std::vector<Event>, \
			CompareEvent > registered_events;
};



#endif 

