#ifndef TCPALGORITHM_H
#define TCPALGORITHM_H

#include "common.hpp"

class Flow;
class Packet;

enum TCPType{
	TCP_RENO_t
};


class TCPAlgorithm {
public:
	TCPAlgorithm() {}

	virtual void alertPacketSent(Packet*) {}
	virtual void updateTransmit();
	virtual void updateAck(int id){}
	//virtual void updateLoss(int id){}
	virtual void rx_timeout(int id){}

	int getNextID(){return next_id;};
	int windowFull();
	int getWindow(){return (int)window_size;};

	void recordRTT(double);
	double getAvgRTT();
	double getMINRTT() { return min_RTT; }

protected:
	Flow* parent_flow;

	int last_rx_ack_id = 0; //it is important that this starts as 0.
	int next_id = 0;
	double window_size = 1;

	double sum_RTT = 0;
	double min_RTT = std::numeric_limits<double>::max();
	int RTT_count = 0;




};

#endif //TCPALGORITHM_H
