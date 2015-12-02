#include "../../include/event/txsrcevent.hpp"
#include "../../include/event/tcptimeoutevent.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/tcpalgorithm/tcpreno.hpp"
#include "../../include/flow.hpp"

int TCPTimeOutEvent::handleEvent(){
	EventQueue::getInstance()->num_non_core--;
	reno->rx_timeout(tx_packet_id);

	Packet* nxt_tx_pkt = reno->parent_flow->genNextPacketFromRx();

	if (nxt_tx_pkt != NULL)
	{
		TxEvent* next_tx = new TxSrcEvent(nxt_tx_pkt);

		next_tx->time = time + reno->parent_flow->getTxDelay();
	}


	return 1;
}


