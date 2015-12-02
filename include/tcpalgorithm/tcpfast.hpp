#ifndef TCPALGORITHM_TCPFAST_H
#define TCPALGORITHM_TCPFAST_H

#include "../tcpalgorithm.hpp"
#include "../flow.hpp"

#include <limits>
#include <map>	

class Flow;

class TCPFast :public TCPAlgorithm {
public:
	TCPFast(Flow* parent_flow);

	void updateAck(int id) override;
	void alertPacketSent(Packet* pkt) override;

private:
	int threshold = std::numeric_limits<int>::max();
	int dup_count = 0;

	void handleDupAck(int);
	void handleNewAck(int);

	void resetNextID();
	std::map<int, double> time_sent;
};

#endif // TCPALGORITHM_TCPFAST_H
