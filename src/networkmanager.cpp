#include "../include/networkmanager.hpp"
#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"

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

int NetworkManager::registerFlow(Flow& flow)
{
	if (m_nodes.count(flow.getSrc()) == 0)
		return -1;

	if (m_nodes.count(flow.getDest()) == 0)
		return -1;

	m_flows[(std::string) flow] = &flow;
	flow.setTxDelay(m_nodes[flow.getSrc()]->\
			getAdjLinks().front()->link_rate);
	return 1;
}

int NetworkManager::registerNode(Node& node)
{
	m_nodes[(std::string) node] = &node;
	return 1;
}

int NetworkManager::registerLink(Link& link)
{
	m_links[(std::string) link] = &link;
	return 1;
}

Flow* NetworkManager::getFlow(std::string id) {
	if (m_flows.count(id) == 0)
		return NULL;

	return m_flows[id];
}

Node* NetworkManager::getNode(std::string id) {
	if (m_nodes.count(id) == 0)
		return NULL;

	return m_nodes[id];
}

Link* NetworkManager::getLink(std::string id) {
	if (m_links.count(id) == 0)
		return NULL;

	return m_links[id];
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

	node2link[node1_id + node2_id] = link_id;
	node2link[node2_id + node1_id] = link_id;
	return 1;
}

#ifdef ROUTING_TEST
Link* NetworkManager::getLinkBtwNodes(std::string node1, std::string node2)
{
	std::string link_id = node2link[node1 + node2];

	if (m_links.count(link_id) == 0)
		return NULL;
		
	return m_links[link_id];
}
#endif

Flow* NetworkManager::resetFlowIterator()
{
	m_flow_iter = m_flows.begin();
	return m_flow_iter->second;
}

Flow* NetworkManager::getNextFlowIterator()
{
	if(++m_flow_iter != m_flows.end())
		return m_flow_iter->second;
	else{
		return NULL;
	}
}

Node* NetworkManager::resetNodeIterator()
{
	m_node_iter = m_nodes.begin();
	return m_node_iter->second;
}

Node* NetworkManager::getNextNodeIterator()
{
	if(++m_node_iter != m_nodes.end())
		return m_node_iter->second;
	else{
		return NULL;
	}
}

Link* NetworkManager::resetLinkIterator()
{
	m_link_iter = m_links.begin();
	return m_link_iter->second;
}

Link* NetworkManager::getNextLinkIterator()
{
	if(++m_link_iter != m_links.end())
		return m_link_iter->second;
	else{
		return NULL;
	}
}
