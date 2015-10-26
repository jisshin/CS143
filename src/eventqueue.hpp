#ifdef EVENT_QUEUE_H
#define EVENT_QUEUE_H

/* C/C++ lib */
#include <stdio.h>
#include <stdlib.h>

/* other lib */
#include "Event.h"

class EventQueue{
	public:
		static EventQueue* get_instance(){
			static S instance; 
			return &instance; 
			count = 0;
		}
		int test_count();
	private:
		EventQueue(){};
		EventQueue(EventQueue const&);	 	 // Don't implement 
		void operator=(EventQueue const&);	 // Dont' implement 
		int count;
};



#endif 

