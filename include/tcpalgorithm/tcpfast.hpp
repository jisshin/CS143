#ifndef TCPALGORITHM_TCPFAST_H
#define TCPALGORITHM_TCPFAST_H

#include "../tcpalgorithm.hpp"
#include "../flow.hpp"

#include <limits>
#include <map>	

class Flow;

const double Gamma = 0.90;
const double alpha = 20;

class TCPFast :public TCPAlgorithm {
public:
	TCPFast(Flow* parent_flow);

	void updateAck(int id) override;
	void alertPacketSent(Packet* pkt) override;

	void updateWindow();
private:
	int threshold = std::numeric_limits<int>::max();
	int dup_count = 0;
	int last_dup = 0;

	void handleDupAck(int);

	void resetNextID();
	std::map<int, double> time_sent;
};

#endif // TCPALGORITHM_TCPFAST_H
