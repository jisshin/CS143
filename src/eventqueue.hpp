#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

/* C/C++ lib */
#include <stdio.h>
#include <stdlib.h>

/* other lib */
#include "event.hpp"

class EventQueue{
	public:
		static EventQueue& get_instance(){
			static EventQueue instance; 
			instance.count = 0;
			return instance; 
	
		}
		int test_count();
	private:
		EventQueue(){};
		EventQueue(EventQueue const&);	 	 // Don't implement 
		void operator=(EventQueue const&);	 // Dont' implement 
		int count;
};



#endif 

