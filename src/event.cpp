#ifndef _MSC_VER
#include "../include/event.hpp"
#include "../../include/event/rxeventfactory.hpp"
#else
#include "event.hpp"
#endif

int Event::commonTransmit(Node* node, Packet* pkt)
{
  int result = node->transmitPacket(pkt);

	// Create receive event if not dropped;
	if (result > 0){
    RxEventFactory rx_fac;
    Link* mid_link = node->lookupRouting(pkt->packet_dest);
    Node* other_node = mid_link->get_other_node(node);
		RxEvent* next_rx = rx_fac.makeRxEvent(mid_link, other_node);
		next_rx->time = time + mid_link->getDelay();
		eventq->push(next_rx);
	}

  return result;
}
