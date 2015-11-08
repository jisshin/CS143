#ifndef _MSC_VER
#include "../include/networkmanager.hpp"
#include "../include/flow.hpp"
#include "../include/link.hpp"
#else
#include "networkmanager.hpp"
#include "flow.hpp"
#include "link.hpp"
#endif

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

int NetworkManager::registerNode(string id, Node& node)
{
	m_nodes[id] = &node;
	return 1;	
}

int NetworkManager::registerLink(string id, Link& link)
{
	m_links[id] = &link;
	return 1;
}

int NetworkManager::connectLink(string link_id, string node1_id, string node2_id)
{
	if (m_nodes.count(node1_id) == 0)
		return -1;

	if (m_nodes.count(node2_id) == 0)
		return -1;	
	
	if (m_links.count(link_id) == 0)
		return -1;

	m_links[link_id]->establishLink(m_nodes[node1_id], m_nodes[node2_id]);
	m_nodes[node1_id]->establishLink(m_links[link_id]);
	m_nodes[node2_id]->establishLink(m_links[link_id]);
	return 1;
}
