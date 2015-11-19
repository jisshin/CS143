#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#include "../include/event/routeevent.hpp"
#include "../include/common.hpp"

#include <cstdlib>
#include <vector>

int main()
{
	std::vector<Link> links;
	std::vector<Node> nodes;

	std::vector<std::string> link_names = {"L1", "L2", "L3", "L4", "L5"};
	std::vector<std::string> node_names = {"H1", "H2", "H3", "H4", "H5" };

	for (int i = 0; i < 5; i++)
	{
		links.push_back(Link(link_names[i], 10000000, 0.01, 6400));
		nodes.push_back(Node(node_names[i]));
	}

	NetworkManager* nm = NetworkManager::getInstance();

	for (int i = 0; i < 5; i++)
	{
		nm->registerLink(links[i]);
		nm->registerNode(nodes[i]);
	}

	nm->connectLink("L1", "H1", "H2");
	nm->connectLink("L2", "H2", "H3");
	nm->connectLink("L3", "H3", "H4");
	nm->connectLink("L4", "H4", "H5");
	nm->connectLink("L5", "H5", "H1");

	RouteEvent *route = new RouteEvent();
	route->time = 0;
	EventQueue* eq = EventQueue::getInstance();

	eq->push(route);

	eq->run();

	return EXIT_SUCCESS;
}
