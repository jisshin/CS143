#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <map>

class Flow;
class FlowInfo;
class Host;
class Link;
class LinkInfo;
class Router;

class NetworkManager {
public:
	static NetworkManager* getInstance();

	int registerFlow(char* id, FlowInfo&);
	int registerHost(char* id);
	int registerLink(char* id, LinkInfo&);
	int registerRouter(char* id);

	int connectLink(char* link_id, char* node1_id, char* node2_id);
	
	Flow* getFlow(char* id) { return m_flows[*id];}
	Host* getHost(char* id) { return m_hosts[*id];}
	Link* getLink(char* id) { return m_links[*id];}
	Router* getRouter(char* id){ return m_routers[*id];}

private:	
	NetworkManager(){}
	static NetworkManager* manager;

	std::map<char, Flow*> m_flows;
	std::map<char, Host*> m_hosts;
	std::map<char, Link*> m_links;
	std::map<char, Router*> m_routers;
};

#endif //NETWORKMANAGER_H