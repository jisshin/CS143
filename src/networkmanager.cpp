#include "networkmanager.hpp"
#include "flow.hpp"
#include "host.hpp"
#include "link.hpp"
#include "router.hpp"

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

int NetworkManager::registerFlow(char* id, Flow&)
{
	return 1;
}

int NetworkManager::registerHost(char* id)
{
	return 1;	
}

int NetworkManager::registerLink(std::string id, Link& link)
{
	m_links[id] = &link;
	return 1;
}

int NetworkManager::registerRouter(char* id)
{
	return 1;
}

int NetworkManager::connectLink(char* link_id, char* node1_id, char* node2_id)
{
	return 1;
}
