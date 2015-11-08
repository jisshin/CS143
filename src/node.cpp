/*
 * node.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: jenniferlin
 */
#include "../include/node.hpp"

std::string Node::lookupRouting(std::string dest){
	return routing_table[dest];
}

double Node::transmitPacket(Packet* tx_packet){
	Link* tx_link = NetworkManager::getInstance()\
			->getFlow(lookupRouting(tx_packet->packet_dest));
	double queue_delay = tx_link->pushPacket();
	if (queue_delay < 0){
		// packet is dropped due to a full link buffer
		return -1;
	}
	return queue_delay + tx_link->getDelay();
}
