#ifndef LINK_H
#define LINK_H

#include "common.hpp"
#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>

class Node;
class Packet;

/**
 * The data structure represents an element(packet)
 *  on the link buffer
 */
class LinkBuffer {
public:
	LinkBuffer(int s, double stime, double etime):
		size(s), \
		start_time(stime), \
		end_time(etime)
	{}

	// Size of packet in byte
	int size;
	// Entry time on the link
	double start_time;
	// Exist time on the link
	double end_time;

#ifdef JISOO
	Packet* packet;
#endif
};

class Link {
public:
	Link(std::string id, double rate, double delay, int buffer_size)\
	: link_rate(rate), \
	  link_delay(delay), \
	  max_buf_size_in_byte(buffer_size),\
	  link_id(id)
	{}

	/**
	 * Push a packet to link buffer
	 */
	int pushPacket(Packet*);

	/**
	 * Pop a packet from link buffer
	 */
	void popPacket(Packet*);

	/**
	 * Establish link between node pointA and pointB
	 */
	int establishLink(Node* pointA, Node* pointB);

	// Accessor funcitons
	double getRate() { return link_rate; }
	double getDelay();
	int getBufferSize() { return max_buf_size_in_byte; }
	Node* get_other_node(Node*);
	double getNumBytesOnLink();
	double getNumBytesThruLink();

	operator std::string() { return link_id; }

	const double link_rate; // in bytes per seconds
	const double link_delay; // in seconds
	const int max_buf_size_in_byte;
	double num_packet_drop = 0;


private:
	// nodes between the link
	Node* A;
	Node* B;
	std::vector<LinkBuffer> link_buffers;
	const std::string link_id;

	double packet_thru = 0;
	double cur_buf_size_in_byte = 0;


};

#endif //LINK_H
