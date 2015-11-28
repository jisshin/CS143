#ifndef TCPALGORITHM_TCPRENO_H
#define TCPALGORITHM_TCPRENO_H

#include "../tcpalgorithm.hpp"

#include <limits>
#include <map>	


class TCPReno:public TCPAlgorithm{
public:
	TCPReno():TCPAlgorithm(){};

	void updateAck(int id) override;
	void rx_timeout(int id) override;

private:
	int threshold = std::numeric_limits<int>::max();
	int fr_window = 0;
	int dup_count = 0;

	void handleDupAck(int);
	void handleNewAck(int);

	void resetNextID();
	std::map<int, int> cancel_timeout;
};

#endif // TCPALGORITHM_TCPRENO_H
