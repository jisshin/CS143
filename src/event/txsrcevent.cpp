#include "../../include/event/txsrcevent.hpp"
#include "../../include/event/tcptimeoutevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/packet.hpp"
#include "../../include/flow.hpp"
#include "../../include/node.hpp"
#include "../../include/common.hpp"


TxSrcEvent::TxSrcEvent(Packet* pPkt) : TxEvent(pPkt, NULL)
{
	NetworkManager* nm = NetworkManager::getInstance();
	tx_node = nm->getNode(pPkt->packet_src);
}

int TxSrcEvent::handleEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();
	EventQueue* eventq = EventQueue::getInstance();

	Flow* tx_flow = nm->getFlow(tx_packet->packet_flow_id);
	commonTransmit(tx_node, tx_packet);
		
	// generate timeout event for the current packet
	tx_packet->start_t = time;
	TCPTimeOutEvent* TimeOutEvent = new TCPTimeOutEvent(tx_flow, tx_packet->packet_seq_id);

	TimeOutEvent->time = time + 3 * tx_flow->getAvgRTT();
	eventq->push(TimeOutEvent);

	Packet* nxt_tx_pkt = tx_flow->genNextPacketFromTx();

	if (nxt_tx_pkt != NULL)
	{
		TxEvent* next_tx = new TxSrcEvent(nxt_tx_pkt);

		next_tx->time = time + tx_flow->getTxDelay();
		eventq->push(next_tx);
	}

	return 1;
}
