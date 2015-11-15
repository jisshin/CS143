#ifndef TCPALGORITHM_TCPRENO_H
#define TCPALGORITHM_TCPRENO_H

#include "../tcpalgorithm.hpp"

class TCPReno:public TCPAlgorithm{
public:
	TCPReno():TCPAlgorithm(){};
	int getNextPacketID() override;
	int updateWindow() override;
	double getNextPacketTime() override;
	void updateRxAck(int id) override;
private:
	int dup_count;
};

#endif // TCPALGORITHM_TCPRENO_H
