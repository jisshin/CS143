#include "../include/event/rxeventfactory.hpp"
#include "../include/event.hpp"
#include "../include/packet.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/flow.hpp"
#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/common.hpp"

Event::Event(double t)
{
	time = t;
	EventQueue::getInstance()->push(this);
}

int Event::commonTransmit(Node* node, Packet* pkt)
{
	int result = node->transmitPacket(pkt);

	// Create receive event if not dropped;
	if (result > 0){

		Link* mid_link = node->lookupRouting(pkt->packet_dest);
		Node* other_node = mid_link->get_other_node(node);

		RxEventFactory rx_fac;
		double event_time = time + mid_link->getDelay();
		RxEvent* next_rx = rx_fac.makeRxEvent(event_time, mid_link, other_node, pkt);
	}
#ifdef JISOO
	else
	{
		std::cout << (std::string)*node << " : " << pkt->packet_type << "-" << pkt->packet_seq_id << " dropped" << std::endl;
	}
#endif
  return result;
}
