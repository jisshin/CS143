#ifndef ACKEVENT_H
#define ACKEVENT_H

#include "../event.hpp"

/* Forward declaration */ 
class Packet;


class AckEvent: public Event
{
	public: 
		AckEvent(std::string owner, int timeout, int id):\
		ack_timeout(timeout),\
		ack_id(id),\
		Event(owner){};
		int handleEvent();

	private:
		int ack_timeout;
		int ack_id;
};

#endif //TXEVENT_H
