#ifndef TCPALGORITHM_H
#define TCPALGORITHM_H

#include "common.hpp"

enum TCPType{
	TCP_RENO_t
};

class TCPAlgorithm {
public:
	TCPAlgorithm() {}
	void updateTransmit();
	virtual void updateAck(int id){}
	//virtual void updateLoss(int id){}
	virtual void rx_timeout(int id){}
	int getNextID(){return next_id;};
	int windowFull();
	int getWindow(){return window_size;};

protected:
	int last_rx_ack_id = -1;
	//int last_tx_ack_id = 0;
	int next_id = 0;
	double window_size = 1;

};

#endif //TCPALGORITHM_H
