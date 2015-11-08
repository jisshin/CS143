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


class Node {
public:
	Node(std::vector<Node*>adj_n, std::vector<Link*>adj_l)\
		: adj_nodes(adj_n),\
		  adj_links(adj_l) {};
	void genRoutingTable();
	std::vector<Node*> getAdjNodes();
	std::vector<Link*> getAdjLinks();
	//std::map<std::string, std::string> getRoutingTable();
	std::string lookupRouting(std::string dest);
	int transmitPacket(Packet* tx_packet){return 1;};
	
private:
	/* 1 adjacent node means host, more than 1 means router */
	std::vector<Node*> adj_nodes;
	std::vector<Link*> adj_links;
	/* routing table uses IDs of nodes created by NetworkManager */
	std::unordered_map<std::string, std::string> routing_table;
};

#endif //NODE_H
