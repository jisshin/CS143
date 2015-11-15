#include "../../include/event/txevent.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"

#include <iostream>
#define DEBUG


int TxEvent::handleEvent() {

#ifdef DEBUG
	std::cout << "txevent: " << (std::string) *tx_node << \
		" " << tx_packet->id << std::endl;
#endif

	return commonTransmit(tx_node, tx_packet);
}
