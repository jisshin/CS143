#ifndef EVENT_TCPFASTUPDATE_H
#define EVENT_TCPFASTUPDATE_H

#include "../event.hpp"
#include "../eventqueue.hpp"

class Flow;

class TCPFastUpdate :public Event {
public:
	TCPFastUpdate() : Event()
	{
		EventQueue::getInstance()->num_non_core++;
	}

	int handleEvent() override;

};

#endif /* EVENT_TCPFASTUPDATE_H */
