#include "../../include/event/rxendevent.hpp"
#include "../../include/event/txsrcevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/flow.hpp"
#include "../../include/link.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"
#include "../../include/common.hpp"

int RxEndEvent::handleEvent()
{
	Packet* rx_packet = rx_link->popPacket();
	rx_node->receivePacket(rx_packet);

#ifdef DEBUG
	std::cout << "rxevent: receive ack packet " << rx_packet->test\
		<< std::endl;
#endif//DEBUG


	NetworkManager* nm = NetworkManager::getInstance();

	Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);

	Packet* new_src_packet = NULL;

#ifndef TESTCASE0
	rx_flow->receive_ack(rx_packet->id);
	// Check if suppose to send out new src packet
	new_src_packet = rx_flow->genNextPacketFromRx();
#endif
	if (new_src_packet != NULL) {
		TxSrcEvent* next_tx = new TxSrcEvent(new_src_packet);
		next_tx->time = time + rx_flow->getTxDelay();
		EventQueue* eventq = EventQueue::getInstance();
		eventq->push(next_tx);
	}

	return 1;
}
