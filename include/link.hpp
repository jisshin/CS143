#ifndef LINK_H
#define LINK_H

#include <queue>
#include <string>
#include <stdint.h>
#include <iostream>

class Node;
class Packet;

class Link {
public:
	Link(std::string id, double rate, double delay, int buffer_size)\
	: link_rate(rate), \
	  link_delay(delay), \
	  max_buf_size_in_byte(buffer_size),\
	  link_id(id)
	{std::cout << "link rate" << rate << std::endl;}

	int pushPacket(Packet*);
	Packet* lastPacket();
	Packet* peekPacket();
	Packet* popPacket();

	int establishLink(Node* pointA, Node* pointB);

	double getRate() { return link_rate; }
	double getDelay();
	int getBufferSize() { return max_buf_size_in_byte; }
	
	Node* get_other_node(Node*);

	operator std::string() { return link_id; }

	const double link_rate; // in bytes per seconds
	const double link_delay; // in seconds
	const int max_buf_size_in_byte;

	double cur_buf_size_in_byte = 0;
	double num_packet_drop = 0;
	double packet_thru = 0;

private:
	const std::string link_id;

	std::queue<Packet*> link_buffer;

	Node* A;
	Node* B;
};

#endif //LINK_H
