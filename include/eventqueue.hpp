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
		static EventQueue* getInstance();

		void push(Event* event);
		Event* pop();

		int size();
		int num_non_core;

		int empty();

		int run();

		static double cur_time;
	private:
		EventQueue(){};
		static EventQueue* eventqueue;

		void initialize();

		std::priority_queue<Event*, std::vector<Event*>, \
			CompareEvent > registered_events;
};

#endif
