#include "../../include/tcpalgorithm/tcpreno.hpp"
#include "../../include/common.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/event/tcptimeoutevent.hpp"
#include "../../include/packet.hpp"
#include "../../include/flow.hpp"
#include <iostream>


void TCPReno::updateAck(int id) {

	if (last_rx_ack_id == id)
	{
		if (++dup_count >= 3)
		{
			handleDupAck(id);
		}
	}
	else
	{
		//the system guarantees this id is biggger
		//than previous acknowledgement. 
		handleNewAck(id);
		last_rx_ack_id = id;
		dup_count = 1;
	}
}

void TCPReno::handleDupAck(int id)
{
	switch (state) {
	case SLOW_START: //it doesn't care about duplicated acknowledgements.
		break;

	case CONG_AVOID: //move to FRFR state
		state = FRFR;
#ifdef JISOO
		if (parent_flow->getFlowID() == DEBUG_FLOW)
		{
			std::cout << "CASE 1:";
		}
#endif
		threshold = (window_size / 2 > 2) ? window_size / 2 : 2;
		fr_window = (window_size / 2 > 1) ? window_size / 2 : 1;
		window_size = window_size / 2 + 3;
		fr_start_window = window_size;
		resetNextID();
		break;

	case TIMEOUT: //wait until you get non dulpicated acknowlegement
		break;

	case FRFR: //perform Fast Recovery
		window_size = (window_size + 1 < 3 * ((double)fr_window) / 2 - 1) ?
			window_size + 1 : 3 * ((double)fr_window) / 2 - 1;
		if (window_size < 1) {
			window_size = 1;
		}
		break;
	}
}

void TCPReno::handleNewAck(int id)
{
	switch (state) {
	case SLOW_START: //we move to congestion avoidance if necessary
		if (window_size >= threshold)
			state = CONG_AVOID;
		break;

	case CONG_AVOID: //this is the center state. 
		break;

	case TIMEOUT: //timeout is over. go to slow start
		state = SLOW_START;
		break;

	case FRFR: //FRFR is over. go to congestion avoidance.
		window_size = fr_window;
		state = CONG_AVOID;
		break;
	}

	switch (state) {
	case SLOW_START:
		window_size++;
		break;

	case CONG_AVOID:
		window_size += 1 / window_size;
		break;
	}
}

void TCPReno::alertPacketSent(Packet* pkt)
{
	// generate timeout event for the current packet
	double event_time = EventQueue::cur_time + 3 * getAvgRTT();
	TCPTimeOutEvent* timeOutEvent = new TCPTimeOutEvent(event_time, this, pkt->packet_seq_id);
}

void TCPReno::rx_timeout(int id){

	if (cancel_timeout.count(id) == 1 && cancel_timeout[id] > 0)
	{
		cancel_timeout[id]--;
		return;
	}

	if (id < last_rx_ack_id)
	{
		//timeout check OK. 
		return;
	}

	//timeout should happen.
	switch (state) {

	case SLOW_START:
	case CONG_AVOID:
		state = TIMEOUT;
		threshold = (window_size / 2 > 2) ? window_size / 2 : 2;
		window_size = 1;
#ifdef JISOO
		if (parent_flow->getFlowID() == DEBUG_FLOW)
		{
			std::cout << "CASE 2:";
		}
#endif
		resetNextID();
		break;

	case TIMEOUT:
		//in this case, we shouldn't set threshold. since at "timeout" state,
		//window size is already 1.
		window_size = 1;
#ifdef JISOO
		if (parent_flow->getFlowID() == DEBUG_FLOW)
		{
			std::cout << "CASE 3:";
		}
#endif
		resetNextID();
		break;

	case FRFR:
		resetNextID();
		window_size = fr_start_window;
		break;
	}
}

void TCPReno::resetNextID()
{
#ifdef JISOO
	if (parent_flow->getFlowID() == DEBUG_FLOW)
	{
		std::cout << "NEXT ID RESET TO " << last_rx_ack_id << " FROM " << next_id << " THRESHOLD " << threshold << std::endl;
	}
#endif
	for (int i = last_rx_ack_id; i < next_id; i++)
	{
		cancel_timeout[i]++;
	}
	next_id = last_rx_ack_id;
}
