#include "../../include/event/txsrcreviveevent.hpp"
#include "../../include/event/txsrcevent.hpp"
#include "../../include/event/tcptimeoutevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/packet.hpp"
#include "../../include/flow.hpp"
#include "../../include/node.hpp"
#include "../../include/common.hpp"


TxSrcReviveEvent::TxSrcReviveEvent(Packet* pPkt) : TxEvent(pPkt, NULL)
{
	NetworkManager* nm = NetworkManager::getInstance();
	tx_node = nm->getNode(pPkt->packet_src);
}

int TxSrcReviveEvent::handleEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();
	EventQueue* eventq = EventQueue::getInstance();

	Flow* tx_flow = nm->getFlow(tx_packet->packet_flow_id);

	Packet* nxt_tx_pkt = tx_flow->genNextPacketFromTx();

	if (nxt_tx_pkt != NULL)
	{
		TxEvent* next_tx = new TxSrcEvent(nxt_tx_pkt);

		next_tx->time = time + tx_flow->getTxDelay();
		eventq->push(next_tx);
	}
	else
	{
		if (tx_flow->getDataAmt() < 0) return -1;

		if (eventq->size() - eventq->num_non_core == 0)
		{
			TxSrcReviveEvent *e = new TxSrcReviveEvent(tx_packet);
			e->time = time + tx_flow->getBaseTxDelay();
			eventq->push(e);
			return 0;
		}
	}
	return 1;
}

