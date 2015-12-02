#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <unordered_map>
#include "common.hpp"

const int BITS_PER_BYTE = 8;

// fixed packet size in byte
const int SRC_PACKET = 0;
const int ACK_PACKET = 1;
const int ROUT_PACKET = 2;

//TODO: need to update these size
const int SRC_SIZE = 1024;
const int ACK_SIZE = 64;
const int ROUT_SIZE = 256;

/* forward declaration class */
class Flow; 

static std::unordered_map<int, const int> SIZE_TABLE( {
	{ SRC_PACKET, SRC_SIZE },
	{ ACK_PACKET, ACK_SIZE },
	{ ROUT_PACKET, ROUT_SIZE }
} );


// Assume that packet size are fix
class Packet {
	public:
		Packet(std::string flow_id, std::string src, std::string dest, int type, int seq_id = 0)\
		: packet_flow_id(flow_id),
		  packet_src(src), 
		  packet_dest(dest), 
		  packet_type(type),
		  packet_seq_id(seq_id)
		{
			packet_size = SIZE_TABLE[packet_type];
		}

		std::string packet_flow_id;
		std::string packet_src;
		std::string packet_dest;
		int packet_type;
		int packet_seq_id;
		double packet_start_t;

		int packet_size;
};


#endif //PACKET_H

