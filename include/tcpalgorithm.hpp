#ifndef TCPALGORITHM_H
#define TCPALGORITHM_H

#include <limits>
#include "common.hpp"

class Flow;
class Packet;
class Flow;

/**
 * Base class for all TCPAlgorithms.
 */
class TCPAlgorithm {
public:
	TCPAlgorithm(Flow* parent) : parent_flow(parent)
	{}

	/**
	 * Factory function to create TCPAlgorithm based on
	 * the algorithm type
	 */
	static TCPAlgorithm* makeTCPAlgorithm(Flow*, int); 

	/**
	 * Entry point to TCPAlgorithm whenever a SRC packet is
	 * sent
	 */
	virtual void alertPacketSent(Packet*) {}

	/**
	 * Entry point to TCPAlgorithm when a ACK packet is
	 * received
	 */
	virtual void alertPacketReceive(Packet*);

	/**
	 * return the next source packet ID
	 */
	int probeNextID(){return next_id;};

	/**
	 * return and update the next source packet ID;
	 */
	int getAndUpdateNextID() { return next_id++; }

	/**
	 * return if TCP window is currently full
	 */
	int windowFull();

	/**
	 * return a RTT time to update AvgRTT and minRTT
	 */
	void recordRTT(double);

	// Accessor functions
	int getWindow(){return (int)window_size;};
	double getAvgRTT();

	double recent_RTT = 0;
	Flow* parent_flow;

protected:
	virtual void updateAck(int id) {}

	int last_rx_ack_id = 0;
	//it is important that this starts as 0.
	int next_id = 0;
	double window_size = 1;
	double sum_RTT = 0;
	double min_RTT = std::numeric_limits<double>::max();
	int RTT_count = 0;

};

#endif //TCPALGORITHM_H
