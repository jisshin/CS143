#ifndef TCPALGORITHM_H
#define TCPALGORITHM_H

class TCPAlgorithm {
public:
	TCPAlgorithm() {}
	virtual int getNextPacketID(){return 0;}
	virtual int updateWindow(int w){return 0;}
	virtual double getNextPacketTime(){return 0;}
	virtual int getWindow();
	virtual void updateAck(int id);
	virtual void updateLoss(int id);
};
#endif //TCPALGORITHM_H
