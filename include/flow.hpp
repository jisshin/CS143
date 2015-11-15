#ifndef FLOW_H
#define FLOW_H

#ifndef _MSC_VER
#include "../include/TCPAlgorithm.hpp"
#else
#include "TCPAlgorithm.hpp"
#endif

#include <string>

//TODO move status constant to a ENUM
//const int PACKET_DROPPED = 0;
const int PACKET_RECEIVED = 1;

class Packet;
class TCPAlgorithm;

class Flow {
public:
	Flow(std::string id, std::string src, std::string dest, int data_amt);
	void update_flow(int id, int status);
	void setTCPStrategy(TCPAlgorithm* alg) { TCP_strategy = alg; }

	std::string getSrc() { return flow_src; }
	std::string getDest() { return flow_dest; }
	int getDataAmt() { return flow_data_amt; }
	void setDataAmt(int new_data_amt) { flow_data_amt = new_data_amt; }
	operator std::string() { return flow_id; }
	int getAckID(int packet_id);
	int setRTTmin(int RTTmin);

	//TCP dependent
	double getTxDelay(double t);
	Packet* genNextPacket();


private:
	std::string flow_id;
	std::string flow_src;
	std::string flow_dest;
	int flow_data_amt;
	TCPAlgorithm* TCP_strategy;
	//int window_size;
	int last_ack_id = 0;
	int dup_count = 0;
	int current_id = 0;
	int outstanding_count = 0;
	double base_tx_delay;
	double last_transmit_t;

	//next_id is just temporary packet id counter to test txevent
	int next_id = 0;
	int window_full_flag = 0;
};



#endif //FLOW_H
