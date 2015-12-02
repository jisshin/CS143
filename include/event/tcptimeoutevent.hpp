#ifndef EVENT_TCPTIMOUTEVENT_H
#define EVENT_TCPTIMOUTEVENT_H

#include "../event.hpp"
#include "../eventqueue.hpp"


class TCPReno;

class TCPTimeOutEvent:public Event{
public:
	TCPTimeOutEvent(TCPReno* tcp, int id) : Event(), reno(tcp)\
	, tx_packet_id(id)
	{
		EventQueue::getInstance()->num_non_core++;
	}


	int handleEvent() override;
private:
	TCPReno* reno;
	int tx_packet_id;
};

#endif /* EVENT_TCPTIMOUTEVENT_H */
