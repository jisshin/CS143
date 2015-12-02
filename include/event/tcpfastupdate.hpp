#ifndef EVENT_TCPFASTUPDATE_H
#define EVENT_TCPFASTUPDATE_H

#include "../event.hpp"
#include "../eventqueue.hpp"

class Flow;

class TCPFastUpdate :public Event {
public:
	TCPFastUpdate(double t) : Event(t)
	{
		EventQueue::getInstance()->num_non_core++;
	}

	int handleEvent() override;

};

#endif /* EVENT_TCPFASTUPDATE_H */
