
#ifndef LINK_H
#define LINK_H

#include <string>
#include <stdint.h>

class Node;

class Link {
public:
	Link(std::string id, int rate, int delay, int buffer_size)\
	: link_rate(rate), \
	  link_delay(delay), \
	  max_buffer_size(buffer_size),\
	  link_id(id)
	{}

	double putPacket();

	int establishLink(Node* pointA, Node* pointB);

	int getRate() { return link_rate; }
	double getDelay() { return link_delay; }
	int getBufferSize() { return max_buffer_size; }
	
	Node* get_other_node(Node*);

	operator std::string() { return link_id; }
	
private:
	int link_rate;
	// in Mbps
	double link_delay;
	int max_buffer_size;
	int curr_buffer_size = 0;
	std::string link_id;

	Node* A;
	Node* B;
};

#endif //LINK_H
