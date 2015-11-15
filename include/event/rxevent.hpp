#ifndef RXEVENT_H
#define RXEVENT_H

#include "../event.hpp"

/* Forward declaration */
class Link;
class Packet;


class RxEvent : public Event
{
	public:
		RxEvent(Link* pLink, Node* pNode) :\
			rx_link(pLink),\
			rx_node(pNode)
	  {}

		int handleEvent();

	private:
		Link* rx_link;
		Node* rx_node;


};

#endif //RXEVENT_H
