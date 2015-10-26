#include "flow.hpp"
#include "host.hpp"
#include "link.hpp"
#include "router.hpp"

static NetworkManager::manager = NULL;

NetworkManager* NetworkManager::getInstance()
{
	if(manager){
		return manager;
	}
	else{
		return (manager = new NetworkManager());
	}
}

int Network::registerFlow(char* id, FlowInfo&)
{

}

int Network::registerHost(char* id)
{
	
}

int Network::registerLink(char* id, LinkInfo&)
{
	
}

int Network::registerRouter(char* id)
{
	
}

int Network::connectLink(char* link_id, char* node1_id, char* node2_id)
{

}
