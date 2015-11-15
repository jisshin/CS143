#ifndef TCPALGORITHM_TCPRENO_H
#define TCPALGORITHM_TCPRENO_H

#include "../tcpalgorithm.hpp"

class TCPReno:public TCPAlgorithm{
public:
	TCPReno():TCPAlgorithm(){};
	int getWindow() override;
	void updateAck(int id) override;
	void updateLoss(int id) override;
};

#endif // TCPALGORITHM_TCPRENO_H
