#include "../include/tcpalgorithm.hpp"
#include "../include/eventqueue.hpp"
#include "../include/packet.hpp"
#include "../include/tcpalgorithm/tcpfast.hpp"
#include "../include/tcpalgorithm/tcpreno.hpp"

TCPAlgorithm* TCPAlgorithm::makeTCPAlgorithm(Flow* flow, int type)
{
	if (type == TCP_RENO_t)
	{
		return new TCPReno(flow);
	}
	else if (type == TCP_FAST_t)
	{
		return new TCPFast(flow);
	}

	return NULL;
}

int TCPAlgorithm::windowFull(){
	return (next_id > window_size + last_rx_ack_id);
}

void TCPAlgorithm::updateTransmit(){
	next_id++;
}

void TCPAlgorithm::alertPacketReceive(Packet* pkt)
{
	recordRTT(EventQueue::cur_time - pkt->start_t);
}

void TCPAlgorithm::recordRTT(double RTT) {
	sum_RTT += RTT;
	RTT_count++;
	recent_RTT = RTT;
	if (RTT < min_RTT) {
		min_RTT = RTT;
	}
}

double TCPAlgorithm::getAvgRTT() {
	if (RTT_count == 0) {
		return 0.1;
	}
	else {
		return sum_RTT / RTT_count;
	}
}