#ifndef EVENT_TCPTIMOUTEVENT_H
#define EVENT_TCPTIMOUTEVENT_H

#include "../event.hpp"
#include "../eventqueue.hpp"


class TCPReno;

class TCPTimeOutEvent:public Event{
public:
	TCPTimeOutEvent(double t, TCPReno* tcp, int id) : Event(t), reno(tcp)\
	, tx_packet_id(id)
	{}


	int handleEvent() override;
private:
	TCPReno* reno;
	int tx_packet_id;
};

#endif /* EVENT_TCPTIMOUTEVENT_H */
