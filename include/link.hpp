
#ifndef LINK_H
#define LINK_H

class Node;

class Link {
public:
	Link(int rate, int delay, int buffer_size, std::string id)\
	: link_rate(rate), \
	  link_delay(delay), \
	  max_buffer_size(buffer_size),\
	  link_id(id)
	{}

	//int getRate() { return link_rate; }
	double getDelay() { return link_delay; }
	//int getBufferSize() { return m_buffer_size; }

	double putPacket();

	int establishLink(Node* pointA, Node* pointB)
	{
		A = pointA;
		B = pointB;
		return 1;
	}

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
