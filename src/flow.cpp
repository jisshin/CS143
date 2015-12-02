#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#include "../include/eventqueue.hpp"
#include "../include/networkmanager.hpp"
#include "../include/event/txsrcevent.hpp"
#include "../include/common.hpp"
#include "../include/tcpalgorithm.hpp"

#include <iostream>

Flow::Flow(std::string id, std::string src, std::string dest, int data_amt, int strategy_type, double start_time)\
: flow_id(id), \
  flow_src(src), \
  flow_dest(dest), \
  flow_data_amt(data_amt)
{
	setTCPStrategy(strategy_type);
	Packet* init_tx_packet = genNextPacketFromTx();
	TxSrcEvent *init_tx = new TxSrcEvent(start_time, init_tx_packet);
}

void Flow::receiveSrcAndGenTx(Packet* pkt)
{
	TCP_strategy->alertPacketSent(pkt);
	packet_sent++;
	pkt = genNextPacketFromTx();

	if (pkt != NULL)
	{
		double event_time = EventQueue::cur_time + getTxDelay();
		TxEvent* next_tx = new TxSrcEvent(event_time, pkt);
	}
}

void Flow::receiveAckAndGenRx(Packet* pkt) 
{
	receive_ack(pkt->packet_seq_id);
	TCP_strategy->alertPacketReceive(pkt);
	pkt = genNextPacketFromRx();

	if (pkt != NULL)
	{
		double event_time = EventQueue::cur_time + getTxDelay();
		TxEvent* next_tx = new TxSrcEvent(event_time, pkt);
	}
}

void Flow::setTCPStrategy(int type)
{
	TCP_strategy = TCPAlgorithm::makeTCPAlgorithm(this, type);
}

void Flow::setTxDelay(double link_rate){
	base_tx_delay = SRC_SIZE/link_rate;
	base_link_rate = link_rate;
	std::cout<<"tx delay"<< base_tx_delay << std::endl;
	base_link_rate = link_rate;
}


void Flow::receive_ack(int id){
	TCP_strategy->updateAck(id);
	packet_receive++;
	//clearTimeout();
}

Packet* Flow::genNextPacketFromTx(){

	// if currently the window is full, don't generate new
	// packet
#ifdef DEBUG
	std::cout << "getting  src packet from TX " << std::endl;
#endif
	if (TCP_strategy->windowFull()){
#ifdef DEBUG
			std::cout<<"window size " << TCP_strategy->getWindow() << std::endl;
			std::cout << "window full" << std::endl;
#endif
			window_full_flag = 1;
			return NULL;
	}

	// send next packet, if window is not full, and have more
	// data to send
#ifdef DEBUG
	std::cout<<"gen src packet from TX: "<< TCP_strategy->getNextID()<< std::endl;
#endif
	window_full_flag = 0;
	return comGenSrcPacket();
}

Packet* Flow::genNextPacketFromRx(){
	// if there's a newly open space in window
	if((window_full_flag)&&(!TCP_strategy->windowFull())){
		window_full_flag = 0;
#ifdef DEBUG
	std::cout<<"gen src packet from RX: "<< TCP_strategy->getNextID()<< std::endl;
#endif
		return comGenSrcPacket();
	}
	return NULL;
}


Packet* Flow::comGenSrcPacket() {
	if (flow_data_amt > 0) {
		Packet* next_packet = new Packet(flow_id, flow_src, \
			flow_dest, SRC_PACKET, TCP_strategy->getNextID());
		flow_data_amt -= next_packet->packet_size;
		TCP_strategy->updateTransmit();
		return next_packet;
	}
	std::cout << "data amount" << flow_data_amt << std::endl;
	return NULL;
}
//TODO: implement genAckPacket and get rid of getAckID
Packet* Flow::genAckPacket(Packet* received_packet)
{
	Packet* ack_packet = NULL;
	int new_ack_flag = 0;
	if (received_packet->packet_seq_id == last_tx_ack_id)
	{
		last_tx_ack_id++;
		new_ack_flag = 1;
	}

	if ((received_packet->packet_seq_id > last_tx_ack_id) || (new_ack_flag))
	{
		ack_packet = new Packet(flow_id, flow_dest, \
			flow_src, ACK_PACKET, last_tx_ack_id);
	}

#ifdef JISOO
	if (received_packet->packet_seq_id > last_tx_ack_id)
		std::cout << flow_id << " : " << received_packet->packet_seq_id << " " << last_tx_ack_id << std::endl;
#endif


	return ack_packet;
}

double Flow::getTxDelay()
{
	double delay = \
			((last_transmit_t + base_tx_delay) > EventQueue::cur_time)?\
					base_tx_delay:0;
	last_transmit_t = EventQueue::cur_time;
	return delay;
}

int Flow::getNumByteSent(){


	int complete_packet = (packet_sent - 1 >= 0)?packet_sent - 1: 0;
	int total_sent = tx_left_over_byte + \
			(complete_packet) * SRC_SIZE;
	// last packet is fully sent
	if (last_transmit_t + base_tx_delay < EventQueue::cur_time){
		total_sent += SRC_SIZE;
		tx_left_over_byte = 0;
	}
	else{
		int fraction = SRC_SIZE* (EventQueue::cur_time - last_transmit_t)/base_tx_delay;
		total_sent += fraction;

		tx_left_over_byte = SRC_SIZE - fraction;
	}
	packet_sent = 0;
	return total_sent;
}

int Flow::getNumByteReceive(){
	int complete_packet = (packet_receive - 1 >= 0)?packet_receive - 1: 0;
	int total_receive = rx_left_over_byte + \
			(complete_packet) * ACK_SIZE;
	// last packet is fully sent
	double base_rx_delay = ACK_SIZE/base_link_rate;
	if (last_rx_ack_t + base_rx_delay < EventQueue::cur_time){
		total_receive += ACK_SIZE;
		rx_left_over_byte = 0;
	}
	else{
		int fraction = SRC_SIZE* (EventQueue::cur_time - last_rx_ack_t)/base_rx_delay;
		total_receive += fraction;
		rx_left_over_byte = ACK_SIZE - fraction;
	}
	packet_receive = 0;
	return total_receive;
}
