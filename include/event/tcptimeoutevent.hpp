#ifndef EVENT_TCPTIMOUTEVENT_H
#define EVENT_TCPTIMOUTEVENT_H

#include "../event.hpp"
#include "../eventqueue.hpp"


class TCPReno;

/**
 * TCPTimeOutEvent implement Event class. This is the
 * timeout event for each SRC packet in TCPReno
 */
class TCPTimeOutEvent:public Event{
public:
	TCPTimeOutEvent(double t, TCPReno* tcp, int id) : Event(t), reno(tcp)\
	, tx_packet_id(id)
	{}

	int handleEvent() override;

private:
	// pointers to the TCPReno object of the parent
	// flow
	TCPReno* reno;

	// SRC packet id to timeout
	int tx_packet_id;
};

#endif /* EVENT_TCPTIMOUTEVENT_H */
