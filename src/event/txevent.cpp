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
#define DEBUG

int TxEvent::handleEvent(){
	NetworkManager* nm = NetworkManager::getInstance();
	EventQueue* eventq = EventQueue::getInstance();

	Node* tx_node = nm->getNode(event_owner);
	Flow* tx_flow = nm->getFlow(tx_packet->packet_flow_id);

#ifdef DEBUG
	std::cout << "txevent: " << event_owner << tx_packet->packet_id << std::endl;
#endif

<<<<<<< HEAD
	//First, transmit packet, and set up rx event
	double delay = tx_node->transmitPacket(tx_packet);
	if(delay >= 0){
		RxEvent* next_rx = new RxEvent(tx_node->lookupRouting(event_owner)\
				,tx_packet);
=======
	//First, transmit packet
	Node* rx_node = NULL
	double delay = tx_node->transmitPacket(tx_packet, rx_node);

	if(delay >= 0){
		RxEvent* next_rx = new RxEvent(rx_node, tx_packet);
		// TODO: update the receive event time with correct
		// value ( according to link delay )
>>>>>>> d8614fc2dcdde4b5bbb9214e1fba40dc5389a1dd
		next_rx->time = time + delay;
		eventq->push(next_rx);
	}
	// if not ack packet, prepare the next tx event
	if (tx_packet->ack_id == -1){
		// generate next_tx event regardless the status of
		// transmit;
		Packet* next_tx_packet = tx_flow->genNextPacket();
		if (next_tx_packet != NULL){
			TxEvent* next_tx = new TxEvent(event_owner,\
						next_tx_packet);
			next_tx->time = tx_flow->get_tx_rate();
			eventq->push(next_tx);
		}
	}
}

