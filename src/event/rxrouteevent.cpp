#include "../../include/event/rxrouteevent.hpp"
#include "../../include/link.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"

int RxRouteEvent::handleEvent()
{
	Packet* rx_packet = rx_link->popPacket();
	rx_node->receivePacket(rx_packet);

	EventQueue* eq = EventQueue::getInstance();
	eq->num_non_core--;

	//get routing table of source packet--simulates packet with routing table info
	NetworkManager* nm = NetworkManager::getInstance();
	Node* nbr = nm->getNode(rx_packet->packet_src);
	Link* link_to_nbr = nm->getLinkBtwNodes(rx_packet->packet_src, *rx_node);

	rx_node->routePacket(nbr, link_to_nbr);
	delete rx_packet;
	return 1;
}
