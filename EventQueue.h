# porgram once 

/* C/C++ lib */
#include <stdio.h>
#include <stdlib.h>

/* other lib */
#include "Event.h"

class EventQueue{
	public:
		EventQueue();
		~EventQueue();
	private:
		static EventQueue *instance;
		Event* dequeue();
		void enqueue(Event* event);
};





