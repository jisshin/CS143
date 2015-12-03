#ifndef TCPALGORITHM_TCPRENO_H
#define TCPALGORITHM_TCPRENO_H

#include "../tcpalgorithm.hpp"

#include <limits>
#include <map>	

class Flow;

enum TCPState {
	SLOW_START, CONG_AVOID, FRFR, TIMEOUT
};

class TCPReno:public TCPAlgorithm{
public:
	TCPReno(Flow* parent_flow):TCPAlgorithm(parent_flow)
	{};

	void alertPacketSent(Packet*) override;
	void updateAck(int id) override;

	void rx_timeout(int id);
private:
	int threshold = std::numeric_limits<int>::max();
	int fr_window = 0;
	int dup_count = 0;


	int fr_start_window = 0;
	void handleDupAck(int);
	void handleNewAck(int);


	TCPState state = SLOW_START;

	void resetNextID();
	std::map<int, int> cancel_timeout;
};

#endif // TCPALGORITHM_TCPRENO_H
