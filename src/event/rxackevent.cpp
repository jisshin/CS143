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
	NetworkManager* nm = NetworkManager::getInstance();
	Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);
	//rx_flow->packet_rcvd += rx_packet->packet_size;

	rx_link->popPacket(rx_packet);
	rx_node->receivePacket(rx_packet);



	Packet* ack_packet = rx_flow->genAckPacket(rx_packet);

	if (ack_packet)
	{
		//rx_flow->packet_sent += ack_packet->packet_size;
		ack_packet->start_t = rx_packet->start_t;
		delete rx_packet;
		// And transmit back to sender
		return commonTransmit(rx_node, ack_packet);
	}
	
	return -1;
}
