#ifndef EVENT_H
#define EVENT_H

/* C/C++ lib */
#include <stdio.h>
#include <stdlib.h>
#include <string>

using std::string; 


class Event{
	public:
		Event();

		virtual int handleEvent() = 0;

	private:
		string dest;
		string src;  
		int 	time; 
};
#endif //EVENT_H