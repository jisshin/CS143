#ifndef EVENT_TCPTIMOUTEVENT_H
#define EVENT_TCPTIMOUTEVENT_H

#include "../event.hpp"
#include "../eventqueue.hpp"

class Flow;

class TCPTimeOutEvent:public Event{
public:
	TCPTimeOutEvent(Flow* flow, int id) : Event(), src_flow(flow)\
	, tx_packet_id(id)
	{
		EventQueue::getInstance()->num_non_core++;
	}


	int handleEvent() override;
private:
	Flow* src_flow;
	int tx_packet_id;
};

#endif /* EVENT_TCPTIMOUTEVENT_H */
