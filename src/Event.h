# porgram once 

/* C/C++ lib */
#include <stdio.h>
#include <stdlib.h>

using std::string; 

enum  EventID_t{
	STUB_EVENT_ID;
};

class Event{
	public:
		Event(EventID_t ID);
		EventID_t EventID;
		string dest;
		string src;  
		uint_t 	time; 
};


