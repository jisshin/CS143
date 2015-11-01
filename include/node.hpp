#ifndef NODE_H
#define NODE_H

/* C/C++ lib */
#include <map>
#include <vector>

using std::map;
using std::vector;
using std::string;

class Node {
public:
	Node(std::vector<Node*> adj_n, std::vector<Link*> adj_l)\
	: adj_nodes(adj_n), \
	  adj_links(adj_l), \
	{}
	void genRoutingTable();
	std::vector<Node*> getAdjNodes();
	std::vector<Link*> getAdjLinks();
	std::map<std::string, std::string> getRoutingTable();
	
private:
	/* 1 adjacent node means host, more than 1 means router */
	std::vector<Node*> adj_nodes;
	std::vector<Link*> adj_links;
	/* routing table uses IDs of nodes created by NetworkManager */
	std::map<std::string, std::string> routing_table;
};

#endif //NODE_H