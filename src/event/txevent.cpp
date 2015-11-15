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
	std::cout << "txevent: " << event_owner<< " " << tx_packet->packet_id << std::endl;
#endif

	//First, transmit packet
	uintptr_t rx_link = NULL;
	int result = tx_node->transmitPacket(tx_packet, &rx_link);

	double delay;

	// Create rx event
	if(result > 0){
		Node* rx_node = (Link*)rx_link->get_other_node(tx_node);
		RxEvent* next_rx = new RxEvent((Link*)rx_link, rx_node);
		next_rx->time = time + (Link*)rx_link->getDelay();
		eventq->push(next_rx);
	}
	// generate next_tx event regardless the status of
	// transmit;
	if(tx_packet->ack_id == -1){
		Packet* next_tx_packet = tx_flow->genNextPacket();
		if (next_tx_packet != NULL){
			TxEvent* next_tx = new TxEvent(event_owner,\
						next_tx_packet);
			// this time should be TCP dependent
			delay = tx_flow->getTxDelay();
			next_tx->time = time + delay;
			eventq->push(next_tx);
		}
	}
	return 1;
}
