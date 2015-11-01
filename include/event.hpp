#ifndef EVENT_H
#define EVENT_H

/* C/C++ lib */
#include <stdio.h>
#include <stdlib.h>
#include <string>

using std::string; 


class Event{
	public:
		Event() {}

		virtual int handleEvent() { return 0; }

	//private:
		string dest;
		string src;  
		double time = -1; 
};

struct CompareEvent
{
	bool operator()(const Event& lhs, const Event& rhs) const
	{
		return lhs.time > rhs.time;
	}
};
#endif //EVENT_H