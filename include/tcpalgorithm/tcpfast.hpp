#ifndef TCPALGORITHM_TCPFAST_H
#define TCPALGORITHM_TCPFAST_H

#include "../tcpalgorithm.hpp"
#include "../flow.hpp"

#include <limits>
#include <map>	


class TCPFast :public TCPAlgorithm {
public:
	TCPFast() :TCPAlgorithm() 
	{
		
	}

	void updateAck(int id) override;
	void rx_timeout(int id) override;
	void alertPacketSent(Packet* pkt) override;

	Flow* flow;

private:
	int threshold = std::numeric_limits<int>::max();
	int dup_count = 0;

	void handleDupAck(int);
	void handleNewAck(int);

	void resetNextID();
	std::map<int, double> time_sent;
};

#endif // TCPALGORITHM_TCPFAST_H
