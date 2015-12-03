#include "../../include/event/tcpfastupdate.hpp"
#include "../../include/tcpalgorithm/tcpfast.hpp"
#include "../../include/event/txsrcevent.hpp"
#include "../../include/flow.hpp"

int TCPFastUpdate::handleEvent() {

	fast->updateWindow();
	
	if (!fast->parent_flow->checkFlowDone())
	{
		TCPFastUpdate* next = new TCPFastUpdate(time + fast->getAvgRTT(), fast);
	}

	Packet* nxt_tx_pkt = fast->parent_flow->genNextPacketFromRx();

	if (nxt_tx_pkt != NULL)
	{
		double event_time = time + fast->parent_flow->getTxDelay();
		TxEvent* next_tx = new TxSrcEvent(event_time, nxt_tx_pkt);
	}

	return 1;
}


