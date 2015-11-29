#include "../../include/event/txsrcevent.hpp"
#include "../../include/event/tcptimeoutevent.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/flow.hpp"

int TCPTimeOutEvent::handleEvent(){
	EventQueue::getInstance()->num_non_core--;
	src_flow->checkTimeout(tx_packet_id);

	Packet* nxt_tx_pkt = src_flow->genNextPacketFromRx();

	if (nxt_tx_pkt != NULL)
	{
		TxEvent* next_tx = new TxSrcEvent(nxt_tx_pkt);

		next_tx->time = time + src_flow->getTxDelay();
		EventQueue::getInstance()->push(next_tx);
	}


	return 1;
}


