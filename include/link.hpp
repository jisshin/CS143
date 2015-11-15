#ifndef LINK_H
#define LINK_H

#include <queue>
#include <string>
#include <stdint.h>

class Node;
class Packet;

class Link {
public:
	Link(std::string id, int rate, int delay, int buffer_size)\
	: link_rate(rate), \
	  link_delay(delay), \
	  max_buf_size_in_byte(buffer_size),\
	  link_id(id)
	{}

	int pushPacket(Packet*);
	Packet* peekPacket();
	Packet* popPacket();

	double getDelay();
	int weight();

	int establishLink(Node* pointA, Node* pointB);

	Node* get_other_node(Node*);

	operator std::string() { return link_id; }

	const int link_rate; // in Mbps
	const double link_delay;
	const int max_buf_size_in_byte;

	int cur_buf_size_in_byte = 0;
	int num_packet_drop = 0;
	int packet_thru = 0;

private:
	const std::string link_id;

	std::queue<Packet*> link_buffer;

	Node* A;
	Node* B;
};

#endif //LINK_H
