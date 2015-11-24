#ifndef TCPALGORITHM_H
#define TCPALGORITHM_H

#include "common.hpp"

enum TCPType{
	TCP_RENO_t
};

class TCPAlgorithm {
public:
	TCPAlgorithm() {}
	virtual int getWindow(){return 0;}
	virtual void updateAck(int id){}
	virtual void updateLoss(int id){}
	virtual void rx_timeout(){}
	double window_size = 1;
};

#endif //TCPALGORITHM_H
