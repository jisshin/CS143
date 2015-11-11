#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <map>
#include <string>

class Flow;
class Node;
class Link;
class Router;

class NetworkManager {
public:
	static NetworkManager* getInstance();

	int registerFlow(Flow&);
	int registerLink(Link&);
	int registerNode(Node&);

	int connectLink(std::string link_id, std::string node1_id, std::string node2_id);
	
	Flow* getFlow(std::string id);
	Node* getNode(std::string id);
	Link* getLink(std::string id);

private:	
	NetworkManager(){}
	static NetworkManager* manager;

	std::map<std::string, Flow*> m_flows;
	std::map<std::string, Node*> m_nodes;
	std::map<std::string, Link*> m_links;
};

#endif //NETWORKMANAGER_H
