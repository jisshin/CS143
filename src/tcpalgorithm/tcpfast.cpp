#include "../../include/tcpalgorithm/tcpfast.hpp"
#include "../../include/event/tcpfastupdate.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/common.hpp"
#include "../../include/packet.hpp"
#include <iostream>
#include <algorithm>

TCPFast::TCPFast(Flow* parent_flow) : TCPAlgorithm(parent_flow)
{
	double start_time = parent_flow->getStartTime() + getAvgRTT();
	TCPFastUpdate* fastupdate = new TCPFastUpdate(start_time, this);
}

void TCPFast::updateAck(int id) {

	if (last_rx_ack_id == id)
	{
		if (++dup_count >= 2)
		{
			handleDupAck(id);
		}
	}
	else
	{
		//the system guarantees this id is biggger
		//than previous acknowledgement. 
		last_rx_ack_id = id;
		dup_count = 1;
	}
}

void TCPFast::handleDupAck(int id)
{
	if (time_sent.count(id) == 0)
	{
		//this shouldn't happen
		std::cout << "TCP FAST ERROR TYPE 1" << std::endl;
		return;
	}

	if (time_sent[id] + 1.5 * getAvgRTT() < EventQueue::cur_time)
	{
		resetNextID();
	}

}

void TCPFast::updateWindow()
{
	double temp = gamma * (min_RTT / getAvgRTT() * window_size + alpha);
	double temp2 = (1 - gamma) * window_size;
	window_size = std::min(2 * window_size, temp + temp2);
}

void TCPFast::alertPacketSent(Packet* pkt)
{
	time_sent[pkt->packet_seq_id] = EventQueue::cur_time;
}

void TCPFast::resetNextID()
{
#ifdef JISOO
	std::cout << "NEXT ID RESET TO " << last_rx_ack_id << " FROM " << next_id << " THRESHOLD " << threshold << std::endl;
#endif

	next_id = last_rx_ack_id;
}