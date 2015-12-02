#include "../../include/tcpalgorithm/tcpfast.hpp"
#include "../../include/event/tcpfastupdate.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/common.hpp"
#include "../../include/packet.hpp"
#include <iostream>

TCPFast::TCPFast(Flow* parent_flow) : TCPAlgorithm(parent_flow)
{
	TCPFastUpdate* fastupdate = new TCPFastUpdate(getAvgRTT());
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
		handleNewAck(id);
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

	if (time_sent[id] + 2 * getAvgRTT() < EventQueue::cur_time)
	{
		resetNextID();
	}
}

void TCPFast::handleNewAck(int id)
{

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