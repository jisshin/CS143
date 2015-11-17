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
const int SRC_SIZE = 1500;

//TODO: need to update these size
const int ACK_SIZE = 40;
const int ROUT_SIZE = 40;

/* forward declaration class */
class Flow; 

const std::unordered_map<int, int> SIZE_TABLE( {
	{ SRC_PACKET, SRC_SIZE },
	{ ACK_PACKET, ACK_SIZE },
	{ ROUT_PACKET, ROUT_SIZE }
} );


// Assume that packet size are fix
class Packet {
	public:
		Packet(std::string flow_id, std::string src, std::string dest, int type)\
		: packet_flow_id(flow_id),
		  packet_src(src), 
		  packet_dest(dest), 
		  packet_type(type)
		{
			//packet_size = SIZE_TABLE[packet_type];
			//hey jennifer i moved this line over here cuz this is
			//what you probably intended to do. anyway, it still
			//doesn't compile due to syntax error. 
		}

		std::string packet_flow_id;
		std::string packet_src;
		std::string packet_dest;
		int packet_type;

		
#ifndef TESTCASE0
		int packet_size;
#else
		int test = 0;
		int packet_size = PACKET_SIZE;
#endif
};


#endif //PACKET_H

