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


using std::unordered_map;
using std::vector;
using std::string;

typedef std::unordered_map<std::string, std::string> routing_table_t;

class Node {
public:
	Node(std::vector<Node*>adj_n, std::vector<Link*>adj_l)\
		: adj_links(adj_l) {};

	// used for default routing table before dynamic routing is
	// implemented
	void addRouting(routing_table_t);

	// lookupRouting return the link for routing to dest
	std::string lookupRouting(std::string dest);

	// transmitPacket put the Packet on the link and return the
	// estimated time for the packet to be transmitted.
	// if packed is dropped, return -1
	double transmitPacket(Packet* tx_packet);
	
private:

	std::vector<Link*> adj_links;

	routing_table_t routing_table;
};

#endif //NODE_H
