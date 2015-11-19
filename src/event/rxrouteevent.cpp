#include "../../include/event/rxrouteevent.hpp"
#include "../../include/link.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"

int RxRouteEvent::handleEvent()
{
	Packet* rx_packet = rx_link->popPacket();
	rx_node->receivePacket(rx_packet);

	delete rx_packet;
	return 1;
}
