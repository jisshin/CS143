#ifndef _MSC_VER
#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#include "../include/event/txevent.hpp"
#else
#include "event/txevent.hpp"
#include "networkmanager.hpp"
#include "eventqueue.hpp"
#include "flow.hpp"
#include "link.hpp"
#include "node.hpp"
#include "packet.hpp"
#endif
#include <cstdlib>

int main()
{
	Flow flow("F1", "H1", "H2", 20);
	Link link("L1", 10, 10, 64);

	Node node1("H1");
	Node node2("H2");

	NetworkManager* nm = NetworkManager::getInstance();

	nm->registerLink(link);
	nm->registerNode(node1);
	nm->registerNode(node2);
	nm->registerFlow(flow);
	
	nm->connectLink("L1", "H1", "H2");

	Packet packet("F1", "H1", "H2", -1);
	TxEvent init_tx("H1", &packet);
	EventQueue* eq = EventQueue::getInstance();

	eq->push(&init_tx);

	eq->run();

	return EXIT_SUCCESS;
}