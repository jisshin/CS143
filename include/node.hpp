#ifndef NODE_H
#define NODE_H

/* C/C++ lib */
#include <map>
#include <vector>
#include <string>
/* forward declaration */
class Packet;
class Node;
class Link;

//map for host destination address -> link to use
typedef std::map<std::string, Link*> routing_table_t;
typedef std::map<std::string, double> routing_table_helper_t;

class Node {

public:

	Node(std::string id): node_id(id)
	{}

	/**
	 * transmit a packet by look up routing table and
	 * push the packet to the corresponding link.
	 */
	int transmitPacket(Packet* tx_packet);

	/**
	 * receive a packet. just update packet_rcvd
	 */
	int receivePacket(Packet*);


	/**
	 * lookupRouting return the link for routing to dest
	 */
	Link* lookupRouting(std::string dest);


	void routePacket(Node*, Link*);
	void resetRouting();
	std::vector<Node*> getAdjNodes();
	std::vector<Link*> getAdjLinks() { return adj_links; };
	operator std::string() { return node_id; }
	void establishLink(Link* link);


	double packet_sent = 0;
	double packet_rcvd = 0;
	routing_table_t routing_table;
	routing_table_helper_t routing_helper_table;

private:
	std::string node_id;
	std::vector<Link*> adj_links;
};

#endif //NODE_H
