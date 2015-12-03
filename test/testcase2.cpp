
#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/logger.hpp"
#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/common.hpp"

#include <cstdlib>
#include <vector>

int main()
{
	std::vector<Link> links;
	std::vector<Node> nodes;

	std::vector<std::string> link_names = { "L1", "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9" };
	std::vector<std::string> node_names = { "S1", "T1", "S2", "T2", "S3", "T3", "R1", "R2", "R3", "R4" };

	for (int i = 0; i < 3; i++)
	{
		links.push_back(Link(link_names[i], 10000000, 0.01, 128000));
	}

	for (int i = 3; i < link_names.size(); i++)
	{
		links.push_back(Link(link_names[i], 12500000, 0.01, 128000));
	}

	for (int i = 0; i < node_names.size(); i++)
	{
		nodes.push_back(Node(node_names[i]));
	}

	NetworkManager* nm = NetworkManager::getInstance();

	for (int i = 0; i < links.size(); i++)
	{
		nm->registerLink(links[i]);
	}
	for (int i = 0; i < nodes.size(); i++)
	{
		nm->registerNode(nodes[i]);
	}

	nm->connectLink("L1", "R1", "R2");
	nm->connectLink("L2", "R2", "R3");
	nm->connectLink("L3", "R3", "R4");
	nm->connectLink("L4", "S2", "R1");
	nm->connectLink("L5", "T2", "R2");
	nm->connectLink("L6", "S3", "R3");
	nm->connectLink("L7", "T1", "R4");
	nm->connectLink("L8", "R1", "S1");
	nm->connectLink("L9", "R4", "T3");

	int type = TCP_FAST_t;
	Flow flow1("F1", "S1", "T1", 35000000, type, 0.5);
	Flow flow2("F2", "S2", "T2", 15000000, type, 10);
	Flow flow3("F3", "S3", "T3", 20000000, type, 20);

	nm->registerFlow(flow1);
	nm->registerFlow(flow2);
	nm->registerFlow(flow3);

	EventQueue* eq = EventQueue::getInstance();
	eq->run();

	Logger * logger = Logger::getInstance();
	delete logger;

	return EXIT_SUCCESS;
}
