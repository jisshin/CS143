#include "../include/networkmanager.hpp"
#include "../include/flow.hpp"
//#include "../include/host.hpp"
#include "../include/link.hpp"
//#include "../include/router.hpp"

using namespace std;

NetworkManager* NetworkManager::manager = NULL;

NetworkManager* NetworkManager::getInstance()
{
	if(manager){
		return manager;
	}
	else{
		return (manager = new NetworkManager());
	}
}

int NetworkManager::registerFlow(string id, Flow& flow)
{
	if (m_nodes.count(flow.getSrc()) == 0)
		return -1;

	if (m_nodes.count(flow.getDest()) == 0)
		return -1;

	m_flows[id] = &flow;
	return 1;
}

int NetworkManager::registerNode(string id, Node&)
{
	return 1;	
}

int NetworkManager::registerLink(string id, Link& link)
{
	m_links[id] = &link;
	return 1;
}

int NetworkManager::connectLink(string link_id, string node1_id, string node2_id)
{
	return 1;
}
