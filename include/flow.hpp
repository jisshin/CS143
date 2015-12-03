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

	/**
	 * record transmission of a source packet and
	 * generate the next TxSrceEvent if there is a
	 * open window space
	 */
	void sendSrcAndGenTx(Packet* pkt);

	/**
	 * record receiption of a Ack packet and generate
	 * the next TxSrcEvent if a window space just open
	 * up due to the Ack packet
	 */
	void receiveAckAndGenRx(Packet* pkt);

	/**
	 * Set TCP_strategy of the flow
	 */
	void setTCPStrategy(int);

	// just accessors
	TCPAlgorithm* getTCPStrategy() { return TCP_strategy; };
	std::string getFlowID() { return flow_id; }
	std::string getSrc() { return flow_src; }
	std::string getDest() { return flow_dest; }
	int getDataAmt() { return flow_data_amt; }
	double getStartTime() { return flow_start_time; }

	operator std::string() { return flow_id; }

	/**
	 * Set tx_base_delay according to the link rate
	 * of the link connect to the source of the flow
	 */
	void setTxDelay(double link_rate);

	/**
	 * Return the transmission delay for the next
	 * source packet
	 */
	double getTxDelay();

	/**
	 * Generate next source packet when an ACK or
	 * timeout occur
	 */
	Packet* genNextPacketFromRx();

	/**
	 * Generate next source packet when a source
	 * packet is successfully sent out.
	 */
	Packet* genNextPacketFromTx();

	/**
	 * Generate the next AckPacket
	 */
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
