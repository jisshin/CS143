#ifndef RXEVENT_H
#define RXEVENT_H

#include "../event.hpp"

/* Forward declaration */ 
class Packet;


class RxEvent : public Event
{
	public: 
		RxEvent(std::string owner,Packet* packet):\
		Event(owner),\
		rx_packet(packet){};
		int handleEvent();
		~RxEvent();

	private:
		Packet* rx_packet;
		std::string event_owner;

};

#endif //RXEVENT_H
