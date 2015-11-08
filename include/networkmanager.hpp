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

	int registerFlow(std::string id, Flow&);
	int registerLink(std::string id, Link&);
	int registerNode(std::string id, Node&);

	int connectLink(std::string link_id, std::string node1_id, std::string node2_id);
	
	Flow* getFlow(std::string id) { return m_flows[id];}
	Node* getNode(std::string id) { return m_nodes[id];}
	Link* getLink(std::string id) { return m_links[id];}

private:	
	NetworkManager(){}
	static NetworkManager* manager;

	std::map<std::string, Flow*> m_flows;
	std::map<std::string, Node*> m_nodes;
	std::map<std::string, Link*> m_links;
};

#endif //NETWORKMANAGER_H
