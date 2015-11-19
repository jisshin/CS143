#ifndef TCPALGORITHM_H
#define TCPALGORITHM_H

enum TCPType{
	TCP_RENO_t
};

class TCPAlgorithm {
public:
	TCPAlgorithm() {}
	virtual double getWindow(){return 0;}
	virtual void updateAck(int id){}
	virtual void updateLoss(int id){}
	double window_size = 1;
};

#endif //TCPALGORITHM_H
