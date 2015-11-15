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

#include <stdint.h>
#include <iostream>
#include <cassert>
#define DEBUG
int RxEvent::handleEvent(){
	NetworkManager* nm = NetworkManager::getInstance();
	EventQueue* eventq = EventQueue::getInstance();
	Node* rx_node = nm->getNode(event_owner);
	Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);

	if(rx_packet->packet_dest == event_owner){


		// generate acknowledge packet if the rx packet is
		// a src packet and has reached the final destination

		if(rx_packet->ack_id == -1){


		#ifdef DEBUG
			std::cout<<"rxevent: receive src packet " << rx_packet->packet_id\
			<<std::endl;
#endif//DEBUG
			// convert to ack packet
			rx_packet->ack_id = rx_flow->getAckID(rx_packet->packet_id);
			std::string dest = rx_packet->packet_src;
			rx_packet->packet_src = rx_packet->packet_dest;
			rx_packet->packet_dest = dest;
			uintptr_t ack_rx_node = NULL;
			// And transmit back to sender
			double delay = rx_node->transmitPacket(rx_packet, &ack_rx_node);

			// Create receive event if not dropped;
			if (delay >= 0){
				RxEvent* next_rx = new RxEvent(*(Node *)ack_rx_node, rx_packet);
				next_rx->time = time + delay;
				eventq->push(next_rx);
			}

		}

		// Update flow if the rx packet is an ack packet
		else{
#ifdef DEBUG
			std::cout<<"rxevent: receive ack packet " << rx_packet->packet_id\
					<<std::endl;
#endif//DEBUG
			rx_flow->receive_ack(rx_packet->packet_id);
			// Check if suppose to send out new src packet
			Packet* new_src_packet = rx_flow->genNextPacketFromRx();
			if(new_src_packet != NULL){
				TxEvent* next_tx = new TxEvent(*(Node *)rx_node, new_src_packet);
				next_tx->time = time + rx_flow->getTxDelay();
				eventq->push(next_tx);
			}
		}
	}

	// If this is not the final destination, forward the packet
	// regardless of whether ack or src
	else{
		uintptr_t tx_node = NULL;
		double delay = rx_node->transmitPacket(rx_packet, &tx_node);
		if (delay >= 0){
			RxEvent* next_rx =  new RxEvent(*(Node*)tx_node, rx_packet);
			next_rx->time = time + delay;
			eventq->push(next_rx);
		}
	}

	return 1;
}

