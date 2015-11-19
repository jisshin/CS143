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

//host destination address -> link to use
typedef std::map<std::string, Link*> routing_table_t;
typedef std::map<std::string, int> routing_table_helper_t;

class Node {

public:

	Node(std::string id): node_id(id)
	{}

	void establishLink(Link* link);

	int transmitPacket(Packet* tx_packet);
	int receivePacket(Packet*);
	
	std::vector<Node*> getAdjNodes();
	std::vector<Link*> getAdjLinks(){return adj_links;};
	void updateRoute();


	operator std::string() { return node_id; }
	// lookupRouting return the link for routing to dest
	Link* lookupRouting(std::string dest);

	void routePacket(Node*, Link*);

    double packet_sent = 0;
    double packet_rcvd = 0;
    
	routing_table_t routing_table;
	routing_table_helper_t routing_helper_table;

private:
	std::string node_id;
	std::vector<Link*> adj_links;
};

#endif //NODE_H
