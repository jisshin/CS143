#ifndef PACKET_H
#define PACKET_H

#include <string>

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
		Flow* parent_flow;

};

#endif //PACKET_H
