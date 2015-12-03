#ifndef FLOW_H
#define FLOW_H

#include <string>
#include <queue>
#include <map>
#include <functional>
//TODO move status constant to a ENUM
//const int PACKET_DROPPED = 0;
const int PACKET_RECEIVED = 1;

class Packet;
class TxEvent;
class TCPAlgorithm;

class Flow {
public:
	Flow(std::string id, std::string src, std::string dest, \
			int data_amt, int strategy_type, double start_time);

	void sendSrcAndGenTx(Packet* pkt);
	void receiveAckAndGenRx(Packet* pkt);

	void setTCPStrategy(int);
	TCPAlgorithm* getTCPStrategy() { return TCP_strategy; };

	std::string getSrc() { return flow_src; }
	std::string getDest() { return flow_dest; }
	int getDataAmt() { return flow_data_amt; }
	double getStartTime() { return flow_start_time; }
	operator std::string() { return flow_id; }

	//TCP dependent
	void setTxDelay(double link_rate);
	double getTxDelay();

	Packet* genNextPacketFromRx();
	Packet* genNextPacketFromTx();
	Packet* genAckPacket(Packet* received_packet);

	int getNumByteSent();
	int getNumByteReceive();
	int checkFlowDone(){return flow_finish;}

private:

	std::string flow_id;
	std::string flow_src;
	std::string flow_dest;
	int flow_data_amt;
	double flow_start_time;
	TCPAlgorithm* TCP_strategy;

	std::priority_queue<int, std::vector<int>, \
		std::greater<int> > unordered_pkts;

	int last_tx_ack_id = 0;
	int packet_receive = 0;
	int packet_sent = 0;
	int tx_left_over_byte =0;
	int rx_left_over_byte = 0;


	double base_tx_delay;
	double base_link_rate;
	double last_transmit_t;
	double last_rx_ack_t;

	int window_full_flag = 0;
	int flow_finish = 0;
	Packet* comGenSrcPacket();

};



#endif //FLOW_H
