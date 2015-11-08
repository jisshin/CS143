
#include "../../include/event/txevent.hpp"
#include "../../include/event/rxevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/packet.hpp"
#include "../../include/flow.hpp"
#include "../../include/node.hpp"

#include <iostream>
#define DEBUG

int TxEvent::handleEvent(){
	Node* tx_node = NetworkManager::getInstance()->\
			getNode(event_owner);
	EventQueue eventq = EventQueue::get_instance();
	Flow* tx_flow = tx_packet->parent_flow;

#ifdef DEBUG
	std::cout << "txevent: " << event_owner << tx_packet->packet_id << std::endl;
#endif

	//First, transmit packet
	double delay = tx_node->transmitPacket(tx_packet);
	if(delay >= 0){
		RxEvent* next_rx = new RxEvent(tx_node->lookupRouting(event_owner)\
				,tx_packet);
		// TODO: update the receive event time with correct
		// value ( according to link delay )
		next_rx->time = time + delay;
		eventq.push(next_rx);
	}

	// generate next_tx event regardless the status of
	// transmit;
	Packet* next_tx_packet = tx_flow->genNextPacket();
	if (next_tx_packet != NULL){
		TxEvent* next_tx = new TxEvent(event_owner,\
					next_tx_packet);
		next_tx->time = time + 1;
		eventq.push(next_tx);
	}
}

