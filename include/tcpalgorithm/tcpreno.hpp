#ifndef TCPALGORITHM_TCPRENO_H
#define TCPALGORITHM_TCPRENO_H

#include "../tcpalgorithm.hpp"

#include <limits>


class TCPReno:public TCPAlgorithm{
public:
	TCPReno():TCPAlgorithm(){};
	//int lost_id = -1;
	void updateAck(int id) override;
	//void updateLoss(int id) override;
	void rx_timeout(int id) override;

private:
	int slow_start = 1;
	int threshold = std::numeric_limits<int>::max();
	int max_window = 0;
	int fr_flag = 0;
	int fr_window = 0;
	int dup_count = 0;
	void packetLoss(int id);
};

#endif // TCPALGORITHM_TCPRENO_H
