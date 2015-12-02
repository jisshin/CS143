
#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/logger.hpp"
#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#include "../include/event/txsrcevent.hpp"
#include "../include/event/logevent.hpp"
#include "../include/common.hpp"
#include "../include/tcpalgorithm/tcpreno.hpp"

#include <cstdlib>
#include <vector>

int main()
{
	std::vector<Link> links;
	std::vector<Node> nodes;

	std::vector<std::string> link_names = {"L0", "L1", "L2", "L3", "L4", "L5"};
	std::vector<std::string> node_names = {"H1", "H2", "R1", "R2", "R3", "R4" };

	links.push_back(Link(link_names[0], 12500000, 0.01, 64000));
	for (int i = 1; i < 5; i++)
	{
		links.push_back(Link(link_names[i], 10000000, 0.01, 64000));
	}
	links.push_back(Link(link_names[5], 12500000, 0.01, 64000));
	for (int i = 0; i < 6; i++)
	{
		nodes.push_back(Node(node_names[i]));
	}

	NetworkManager* nm = NetworkManager::getInstance();

	for (int i = 0; i < 6; i++)
	{
		nm->registerLink(links[i]);
		nm->registerNode(nodes[i]);
	}

	nm->connectLink("L0", "H1", "R1");
	nm->connectLink("L1", "R1", "R2");
	nm->connectLink("L2", "R1", "R3");
	nm->connectLink("L3", "R2", "R4");
	nm->connectLink("L4", "R3", "R4");
	nm->connectLink("L5", "R4", "H2");

	Flow flow("F1", "H1", "H2", 20000000);

	flow.setTCPStrategy(TCP_RENO_t);
	nm->registerFlow(flow);
	Packet* init_tx_packet = flow.genNextPacketFromTx();
	TxSrcEvent *init_tx = new TxSrcEvent(init_tx_packet);
	init_tx->time = 0.5;
	EventQueue* eq = EventQueue::getInstance();

	eq->run();

	Logger * logger = Logger::getInstance();
	delete logger;

	return EXIT_SUCCESS;
}
