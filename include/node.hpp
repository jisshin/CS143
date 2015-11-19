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
typedef std::unordered_map<std::string, std::pair<Link*, int> > routing_table_t;

class Node {
public:
#ifdef ROUTING_TEST
	Node(std::string id, std::pair<Link*,int >link_entry): node_id(id)
	{

		routing_table = routing_table_t( {id, {link_entry}} );
	}
#endif //ROUTING_TEST
	Node(std::string id):node_id(id){}

	void establishLink(Link* link);

	// transmitPacket put the Packet on the link and return the
	// estimated time for the packet to be transmitted.
	// if packed is dropped, return -1
	int transmitPacket(Packet* tx_packet);
	int receivePacket(Packet*);
	
	std::vector<Node*> getAdjNodes();
	std::vector<Link*> getAdjLinks(){return adj_links;};
	void updateRoute();
	routing_table_t getRoutingTable();

	operator std::string() { return node_id; }
	// lookupRouting return the link for routing to dest
	Link* lookupRouting(std::string dest);

    double packet_sent = 0;
    double packet_rcvd = 0;
    
private:
	std::string node_id;
	std::vector<Link*> adj_links;
	routing_table_t routing_table;
};

#endif //NODE_H
