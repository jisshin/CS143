#ifndef NODE_H
#define NODE_H

/* C/C++ lib */
#include <unordered_map>
#include <vector>
#include <string>
/* forward declaration */
class Packet;
class Node;
class Link;

//host destination address -> link to use
typedef std::unordered_map<std::string, Link*> routing_table_t;

class Node {
public:
	Node(std::string id): node_id(id) 
	{}

	void establishLink(Link* link);

	// transmitPacket put the Packet on the link and return the
	// estimated time for the packet to be transmitted.
	// if packed is dropped, return -1
	double transmitPacket(Packet* tx_packet);
	
	operator std::string() { return node_id; }
private:
	// lookupRouting return the link for routing to dest
	Link* lookupRouting(std::string dest);

	std::string node_id;
	std::vector<Link*> adj_links;

	routing_table_t routing_table;
};

#endif //NODE_H
