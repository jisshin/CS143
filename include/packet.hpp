#ifndef PACKET_H
#define PACKET_H

#include <string>

const int BITS_PER_BYTE;

/* forward declaration class */
class Flow; 

// Assume that packet size are fix
class Packet {
	public:
		Packet(std::string src, std::string dest, int id, \
			Flow* flow)\
		: packet_src(src), \
		  packet_dest(dest), \
		  packet_id(id),
		  parent_flow(flow){};

		std::string packet_src;
		std::string packet_dest;
		int packet_id;
		// -1 for source packet as default
		int ack_id = -1;
		Flow* parent_flow;
		// fixed packet size in byte
		static int packet_size;
};

#endif //PACKET_H
