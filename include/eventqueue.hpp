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

		/**
		 * push the event on EventQueue.
		 */
		void push(Event* event);


		/**
		 * Return singleton EventQueue object
		 */
		static EventQueue* getInstance();

		/**
		 * Return number of element in EventQueue
		 */
		int size();

		/**
		 * Return 1 if EventQueue is empty
		 */
		int empty();

		/**
		 * Runs the network simulation by untill EventQueue
		 * is empty
		 */
		int run();

		int num_non_core;

		static double cur_time;

	private:

		/**
		 * pop an event from the top of the EventQueue,
		 * which should be the next event based on
		 * time.
		 */
		Event* pop();

		// Make the constructor private so that
		// no other code can create another EventQueue
		// object
		EventQueue(){};

		static EventQueue* eventqueue;

		/**
		 * Initialize resetEvent and logEvent
		 */
		void initialize();

		std::priority_queue<Event*, std::vector<Event*>, \
			CompareEvent > registered_events;
};

#endif
