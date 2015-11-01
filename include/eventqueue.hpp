#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

/* C/C++ lib */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
/* other lib */
#include "event.hpp"

class EventQueue{
	public:
		static EventQueue& get_instance(){
			static EventQueue instance; 
			instance.count = 0;
			return instance; 
	
		}
		
		void push(double time, Event event);
		Event pop();

	private:
		EventQueue(){};
		EventQueue(EventQueue const&);	 	 // Don't implement 
		void operator=(EventQueue const&);	 // Dont' implement 
		
		std::map<double, std::vector<Event>> registered_events;

};



#endif 

