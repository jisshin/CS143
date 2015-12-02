#ifndef TCPALGORITHM_H
#define TCPALGORITHM_H

#include <limits>
#include "common.hpp"

class Flow;
class Packet;

enum TCPType{
	TCP_RENO_t, TCP_FAST_t
};

class Flow;

class TCPAlgorithm {
public:
	TCPAlgorithm(Flow* parent) : parent_flow(parent)
	{}

	static TCPAlgorithm* makeTCPAlgorithm(Flow*, int); 

	virtual void alertPacketSent(Packet*) {}
	virtual void alertPacketReceive(Packet*);

	virtual void updateTransmit();
	virtual void updateAck(int id){}

	int getNextID(){return next_id;};
	int windowFull();
	int getWindow(){return (int)window_size;};

	void recordRTT(double);
	double getAvgRTT();
	double recent_RTT = 0;

	Flow* parent_flow;
protected:


	int last_rx_ack_id = 0; //it is important that this starts as 0.
	int next_id = 0;
	double window_size = 1;

	double sum_RTT = 0;
	double min_RTT = std::numeric_limits<double>::max();
	int RTT_count = 0;

};

#endif //TCPALGORITHM_H
