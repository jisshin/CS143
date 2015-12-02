#ifndef FLOW_H
#define FLOW_H

#include <string>
#include <queue>
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

	void receiveSrcAndGenTx(Packet* pkt);
	void receiveAckAndGenRx(Packet* pkt);

	void setTCPStrategy(int);
	TCPAlgorithm* getTCPStrategy() { return TCP_strategy; };

	std::string getSrc() { return flow_src; }
	std::string getDest() { return flow_dest; }
	operator std::string() { return flow_id; }

	//TCP dependent
	void setTxDelay(double link_rate);
	double getTxDelay();

	Packet* genNextPacketFromRx();
	Packet* genNextPacketFromTx();
	Packet* genAckPacket(Packet* received_packet);

	int getNumByteSent();
	int getNumByteReceive();

private:
	void receive_ack(int id);

	std::string flow_id;
	std::string flow_src;
	std::string flow_dest;
	int flow_data_amt;
	TCPAlgorithm* TCP_strategy;


	int last_tx_ack_id = 0;
	int packet_receive = 0;
	int packet_sent = 0;
	int tx_left_over_byte =0;
	int rx_left_over_byte = 0;


	double base_tx_delay;
	double base_link_rate;
	double last_transmit_t;
	double last_rx_ack_t;

	//int next_id = 0;
	int window_full_flag = 0;
	Packet* comGenSrcPacket();

};



#endif //FLOW_H
