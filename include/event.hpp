#ifndef EVENT_H
#define EVENT_H

/* C/C++ lib */
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

class Event{
	public:
		Event(){};
		Event(std::string owner):event_owner(owner){};
		~Event(){};

		virtual int handleEvent(){std::cout<< "fail"<<std::endl;
		return 0;}
		//private:
		//std::string event_dest;
		//std::string evemt_src;  
		std::string event_owner;
		double time = -1;
};

/*
 * Function used by "eventqueue" to order each events. We will
 * prioritize events that happens faster. This comparator will
 * be used by eventqueue to order events correctly.
 */
struct CompareEvent
{
	bool operator()(const Event& lhs, const Event& rhs) const
	{
		return lhs.time > rhs.time;
	}
};
#endif //EVENT_H
