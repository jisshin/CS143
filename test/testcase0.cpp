
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

int main()
{
	Link link("L1", 10000000, 0.01, 64000);

	Node node1("H1");
	Node node2("H2");
	NetworkManager* nm = NetworkManager::getInstance();

	nm->registerLink(link);
	nm->registerNode(node1);
	nm->registerNode(node2);

	nm->connectLink("L1", "H1", "H2");

	Flow flow("F1", "H1", "H2", 20000000, TCP_RENO_t, 1);
	nm->registerFlow(flow);

	EventQueue* eq = EventQueue::getInstance();
	eq->run();

	Logger * logger = Logger::getInstance();
	delete logger;

	return EXIT_SUCCESS;
}
