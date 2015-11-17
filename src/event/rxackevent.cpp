#include "../../include/event/rxackevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/flow.hpp"
#include "../../include/link.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"
#include "../../include/common.hpp"

#include <iostream>

int RxAckEvent::handleEvent()
{
	Packet* rx_packet = rx_link->popPacket();
	rx_node->receivePacket(rx_packet);

#ifdef DEBUG
	std::cout << "rxevent: receive ack packet " << rx_packet->packet_seq_id \
		<< std::endl;
#endif//DEBUG

	NetworkManager* nm = NetworkManager::getInstance();
	Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);

	// convert to ack packet

#ifndef TESTCASE0
	Packet* ack_packet = rx_flow->genAckPacket(rx_packet);
#else
	Packet* ack_packet = new Packet(*rx_flow, rx_packet->packet_dest,\
		rx_packet->packet_src, ACK_PACKET);
	ack_packet->test = rx_packet->test;
#endif
	// And transmit back to sender
	return commonTransmit(rx_node, ack_packet);
}
