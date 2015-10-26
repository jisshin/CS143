#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <map>
#include <string>

class Flow;
class Host;
class Link;
class Router;

class NetworkManager {
public:
	static NetworkManager* getInstance();

	int registerFlow(std::string id, Flow&);
	int registerHost(std::string id);
	int registerLink(std::string id, Link&);
	int registerRouter(std::string id);

	int connectLink(std::string link_id, std::string node1_id, std::string node2_id);
	
	Flow* getFlow(std::string id) { return m_flows[id];}
	Host* getHost(std::string id) { return m_hosts[id];}
	Link* getLink(std::string id) { return m_links[id];}
	Router* getRouter(std::string id){ return m_routers[id];}

private:	
	NetworkManager(){}
	static NetworkManager* manager;

	std::map<std::string, Flow*> m_flows;
	std::map<std::string, Host*> m_hosts;
	std::map<std::string, Link*> m_links;
	std::map<std::string, Router*> m_routers;
};

#endif //NETWORKMANAGER_H