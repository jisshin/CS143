#ifndef TCPALGORITHM_H
#define TCPALGORITHM_H

class TCPAlgorithm {
public:
	TCPAlgorithm() {}
	virtual int getWindow(){return 0;}
	virtual void updateAck(int id){}
	virtual void updateLoss(int id){}
	int window_size;
};
#endif //TCPALGORITHM_H
