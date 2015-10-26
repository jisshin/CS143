#ifndef EVENT_H
#define EVENT_H

/* C/C++ lib */
#include <stdio.h>
#include <stdlib.h>
#include <string>

using std::string; 

enum EventID_t{
	STUB_EVENT_ID
};

class Event{
	public:
		Event(EventID_t ID);
		EventID_t EventID;
		string dest;
		string src;  
		int 	time; 
};
#endif //EVENT_H