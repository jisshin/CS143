
#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include "../include/packet.hpp"
#include "../include/event/txsrcevent.hpp"
#include "../include/common.hpp"

#include <cstdlib>

int main()
{
	Link link("L1", 10, 3, 64);

	Node node1("H1");
	Node node2("H2");

	NetworkManager* nm = NetworkManager::getInstance();

	nm->registerLink(link);
	nm->registerNode(node1);
	nm->registerNode(node2);

	nm->connectLink("L1", "H1", "H2");
	//temporarily moved here. 
	Flow flow("F1", "H1", "H2", 20);
	nm->registerFlow(flow);

#ifndef TESTCASE0
	Packet* init_tx_packet = flow.genNextPacketFromTx();
#else
	Packet* init_tx_packet = new Packet(flow, flow.getSrc(), \
		flow.getDest(), 0);
#endif
	TxSrcEvent init_tx(init_tx_packet);
	init_tx.time = 0;
	EventQueue* eq = EventQueue::getInstance();

	eq->push(&init_tx);

	eq->run();

	printf("# packet dropped: %d\n", link.num_packet_drop);
	return EXIT_SUCCESS;
}
