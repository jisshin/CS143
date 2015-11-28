#include "../../include/event/rxendevent.hpp"
#include "../../include/event/txsrcreviveevent.hpp"
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
	rx_link->popPacket(rx_packet);
	rx_node->receivePacket(rx_packet);

#ifdef CHECK_DROP
	std::cout << "receive ack " << rx_packet->packet_seq_id\
		<<std::endl;
#endif//DEBUG


	NetworkManager* nm = NetworkManager::getInstance();

	Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);

	Packet* new_src_packet = NULL;

	rx_flow->receive_ack(rx_packet->packet_seq_id);
	rx_flow->recordRTT(time - rx_packet->start_t);
	// Check if suppose to send out new src packet
	new_src_packet = rx_flow->genNextPacketFromRx();

	EventQueue* eventq = EventQueue::getInstance();
	if (new_src_packet != NULL) {
		TxSrcEvent* next_tx = new TxSrcEvent(new_src_packet);
		next_tx->time = time + rx_flow->getTxDelay();

		eventq->push(next_tx);
	}
	else
	{
		if (rx_flow->getDataAmt() < 0) return -1;

		if (eventq->size() - eventq->num_non_core == 0)
		{
			TxSrcReviveEvent *e = new TxSrcReviveEvent(rx_packet);
			e->time = time + rx_flow->getBaseTxDelay();
			eventq->push(e);
			return 0;
		}
	}
	delete rx_packet;
	return 1;
}
