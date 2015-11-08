#ifndef TXEVENT_H
#define TXEVENT_H

#include "../event.hpp"
#include <iostream>
#include <string>
/* Forward declaration */ 
class Packet;

class TxEvent:public Event {
public:
	TxEvent(std::string owner, Packet* packet):Event(owner),\
	tx_packet(packet){};
	int handleEvent();

private:
	Packet* tx_packet;
};

#endif //TXEVENT_H



