#include "../../include/event/txsrcevent.hpp"
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
#ifdef DEBUG
	std::cout << "txevent: " << (std::string) *tx_node << \
		" " << tx_packet->test << std::endl;
#endif

	commonTransmit(tx_node, tx_packet);

	// if this is the first tx event from source,
	// check if next packet is available from flow, generate next_tx event regardless the status of
	// transmit;
	NetworkManager* nm = NetworkManager::getInstance();
	Flow* tx_flow = nm->getFlow(tx_packet->packet_flow_id);

#ifndef TESTCASE0
	Packet* nxt_tx_pkt = tx_flow->genNextPacketFromTx();
#else
	Packet* nxt_tx_pkt;
	if (testcase0_counter < MAX_LOOP)
	{
		nxt_tx_pkt = new Packet(*tx_flow, tx_flow->getSrc(), \
			tx_flow->getDest(), SRC_PACKET);
		nxt_tx_pkt->test = ++testcase0_counter;
	}
	else
	{
		return 1;
	}
#endif
	if (nxt_tx_pkt != NULL) {
		TxEvent* next_tx = new TxSrcEvent(nxt_tx_pkt);

#ifndef TESTCASE0
		next_tx->time = time + tx_flow->getTxDelay();
#else
		next_tx->time = time + 1;
#endif
		EventQueue* eventq = EventQueue::getInstance();
		eventq->push(next_tx);
	}

	return 1;
}
