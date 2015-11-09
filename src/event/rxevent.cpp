#ifndef _MSC_VER
#include "../../include/event/txevent.hpp"
#include "../../include/event/rxevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/packet.hpp"
#include "../../include/flow.hpp"
#include "../../include/node.hpp"
#else
#include "txevent.hpp"
#include "rxevent.hpp"
#include "../networkmanager.hpp"
#include "../eventqueue.hpp"
#include "../packet.hpp"
#include "../flow.hpp"
#include "../node.hpp"
#endif

#include <iostream>

int RxEvent::handleEvent(){
	NetworkManager* nm = NetworkManager::getInstance();
	EventQueue* eventq = EventQueue::getInstance();
	Node* rx_node = nm->getNode(event_owner);
	Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);


	// generate acknowledge packet if the rx packet is
	// a src packet
	if(rx_packet->ack_id == -1){
		// TODO ack_id should be updated according to
		// TCP, use 1 for now to differentiate ack and
		// src packet

		// convert to ack packet
		rx_packet->ack_id = 1;
		std::string dest = rx_packet->packet_src;
		rx_packet->packet_src = rx_packet->packet_dest;
		rx_packet->packet_dest = dest;

		// And transmit back to sender
		double delay = rx_node->transmitPacket(rx_packet);
		// Create receive event if not dropped;
		if (delay >= 0){
			RxEvent* next_rx = new RxEvent(rx_node, rx_packet);
			next_rx->time = time + delay;
			eventq->push(next_rx);
		}
	}

	// Update flow if the rx packet is an ack packet
	else{
		rx_flow->update_flow(rx_packet->packet_id, PACKET_RECEIVED)
	}
}

