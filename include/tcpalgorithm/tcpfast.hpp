#ifndef TCPALGORITHM_TCPFAST_H
#define TCPALGORITHM_TCPFAST_H

#include "../tcpalgorithm.hpp"
#include "../flow.hpp"
#include "../common.hpp"

#include <limits>
#include <map>	

class Flow;

/**
 * TCPFast implement TCPAlgorithm
 */
class TCPFast :public TCPAlgorithm {
public:
	TCPFast(Flow* parent_flow);

	/**
	 * updateAck should be called when any ack packet
	 * is received at src
	 * This function will handle timeout if an dup
	 * ACK packet is received.
	 */
	void updateAck(int id) override;

	/**
	 * alertPacketSent should be called when any
	 * SRC packet is sent from src.
	 */
	void alertPacketSent(Packet* pkt) override;

	/**
	 * Update window should be call periodically to update
	 * window size based on RTT
	 */
	void updateWindow();

private:

	void handleDupAck(int);

	void resetNextID();

	// Threshold for slow start
	//int threshold = std::numeric_limits<int>::max();
	int dup_count = 0;
	int last_dup = 0;

	// Map that store the sent time and packet ID pair.
	std::map<int, double> time_sent;
};

#endif // TCPALGORITHM_TCPFAST_H
