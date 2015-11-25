#include "../include/event/rxeventfactory.hpp"
#include "../include/event.hpp"
#include "../include/packet.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/flow.hpp"
#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"

int Event::commonTransmit(Node* node, Packet* pkt)
{
	int result = node->transmitPacket(pkt);

	// Create receive event if not dropped;
	if (result > 0){

		Link* mid_link = node->lookupRouting(pkt->packet_dest);
		Node* other_node = mid_link->get_other_node(node);

		RxEventFactory rx_fac;
		RxEvent* next_rx = rx_fac.makeRxEvent(mid_link, other_node, pkt);

		next_rx->time = time + mid_link->getDelay();
		
		EventQueue* eventq = EventQueue::getInstance();
		eventq->push(next_rx);
	}
  pkt->start_t = time;
  return result;
}

int Event::commonIsSimOver()
{
	NetworkManager* nm = NetworkManager::getInstance();
	Flow* flow = nm->resetFlowIterator();
	while (flow != NULL)
	{
		if (flow->getDataAmt() > 0)
		{
			//still some data left to send

			return 0;
		}
		flow = nm->getNextFlowIterator();
	}

	//all data is sent. simulation is over

	std::cout << "data sim done " << std::endl;
	return 1;
}
