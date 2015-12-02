#ifndef FLOW_H
#define FLOW_H

#include "../include/tcpalgorithm.hpp"


#include <limits>
#include <string>
#include <queue>
//TODO move status constant to a ENUM
//const int PACKET_DROPPED = 0;
const int PACKET_RECEIVED = 1;

class Packet;
class TCPAlgorithm;

class Flow {
public:
	Flow(std::string id, std::string src, std::string dest, int data_amt);

	void receive_ack(int id);
	void setTCPStrategy(TCPAlgorithm* alg) { TCP_strategy = alg; }

	std::string getSrc() { return flow_src; }
	std::string getDest() { return flow_dest; }
	int getDataAmt() { return flow_data_amt; }
	operator std::string() { return flow_id; }
	int getAckID(int packet_id);

	// TODO: implement setRTT and set base tx delay when
	// registering flow
	void setRTTmin(double RTTmin);
	void setTxDelay(double link_rate);

	//TCP dependent
	double getTxDelay();
	Packet* genNextPacketFromRx();
	Packet* genNextPacketFromTx();
	Packet* genAckPacket(Packet* received_packet);

	TCPAlgorithm* getTCPStrategy(){return TCP_strategy;};
	int checkTimeout(int id);
	int getNumByteSent();
	void alertPacketSent(Packet* pkt);

	double packet_rcvd = 0;
	double recent_RTT = 0;

private:
	std::string flow_id;
	std::string flow_src;
	std::string flow_dest;
	int flow_data_amt;
	TCPAlgorithm* TCP_strategy;

	// For getNumByteSent()
	int left_over_byte = 0;
	int packet_sent = 0;

	//int last_rx_ack_id = -1;
	int last_tx_ack_id = 0;
	//int dup_count = 0;
	//int outstanding_count = 0;
	double base_tx_delay;
	double last_transmit_t;

	//int next_id = 0;
	int window_full_flag = 0;
	Packet* comGenSrcPacket();

};



#endif //FLOW_H
