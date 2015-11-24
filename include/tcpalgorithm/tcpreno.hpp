#ifndef TCPALGORITHM_TCPRENO_H
#define TCPALGORITHM_TCPRENO_H

#include "../tcpalgorithm.hpp"

class TCPReno:public TCPAlgorithm{
public:
	TCPReno():TCPAlgorithm(){};
	int getWindow() override;
	int lost_id = -1;
	void updateAck(int id) override;
	void updateLoss(int id) override;
	void rx_timeout() override;
private:
	int slow_start = 1;
	int threshold = INFINITY_32;
	int max_window = 0;
	int fr_flag = 0;
	int fr_window = 0;
};

#endif // TCPALGORITHM_TCPRENO_H
