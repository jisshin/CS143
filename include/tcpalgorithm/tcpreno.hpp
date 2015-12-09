#ifndef TCPALGORITHM_TCPRENO_H
#define TCPALGORITHM_TCPRENO_H

#include "../tcpalgorithm.hpp"

#include <limits>
#include <map>	

class Flow;

enum TCPState {
	SLOW_START, CONG_AVOID, FRFR, TIMEOUT
};

/**
 * TCPReno implement TCPAlgorithm
 */
class TCPReno:public TCPAlgorithm{
public:
	TCPReno(Flow* parent_flow):TCPAlgorithm(parent_flow)
	{};

	/**
	 * updateAck should be called when any ack packet
	 * is received at src
	 * This function will update the state machine.
	 */
	void updateAck(int id) override;

	/**
	 * alertPacketSent should be called when any
	 * SRC packet is sent from src.
	 */
	void alertPacketSent(Packet*) override;

	/**
	 * This function is called to handle any recevied
	 * timeout event for with the associated packet
	 * id. The state machine will be updated
	 */
	void rx_timeout(int id);

private:
	// Handle a dup ACK
	void handleDupAck(int);
	// handle a non-dup ACK
	void handleNewAck(int);
	// reset NextID for SRC packet for retransmission
	void resetNextID();

	//Initial threshold = inf
	int threshold = std::numeric_limits<int>::max();
	int fr_window = 0;
	int dup_count = 0;
	int fr_start_window = 0;
	// Initial TCP state = SLOW_START
	TCPState state = SLOW_START;

	// Map stores the packet id/numer of packet sent pairs
	std::map<int, int> cancel_timeout;
};

#endif // TCPALGORITHM_TCPRENO_H
