#ifndef PACKET_H
#define PACKET_H

#include <string>

const int BITS_PER_BYTE = 8;

// fixed packet size in byte
const int PACKET_SIZE = 10;

/* forward declaration class */
class Flow; 

// Assume that packet size are fix
class Packet {
	public:
		Packet(std::string flow_id, std::string src, std::string dest, int id)\
		: packet_flow_id(flow_id),\
		  packet_src(src), \
		  packet_dest(dest), \
		  packet_id(id)
		{};

		std::string packet_flow_id;
		std::string packet_src;
		std::string packet_dest;
		int packet_id;
		// -1 for source packet as default
		int ack_id = -1;
};

#endif //PACKET_H
