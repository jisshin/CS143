#include "../../include/event/rxfwdevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/flow.hpp"
#include "../../include/link.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"

int RxFwdEvent::handleEvent()
{
	Packet* rx_packet = rx_link->popPacket();
	rx_node->receivePacket(rx_packet);
	commonTransmit(rx_node, rx_packet);

	return 1;
}
