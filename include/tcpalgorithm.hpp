#ifndef TCPALGORITHM_H
#define TCPALGORITHM_H

#include "common.hpp"

enum TCPType{
	TCP_RENO_t
};

enum TCPState {
	SLOW_START, CONG_AVOID, FRFR, TIMEOUT
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
	int getWindow(){return (int)window_size;};

protected:
	int last_rx_ack_id = 0; //it is important that this starts as 0.
	//int last_tx_ack_id = 0;
	int next_id = 0;
	double window_size = 1;

	TCPState state = SLOW_START;

};

#endif //TCPALGORITHM_H
