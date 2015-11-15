#include "../../include/event/rxfwdevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/flow.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"

int RxFwdEvent::handleEvent()
{
	RxEvent::handleEvent();
  commonTransmit(rx_node, rx_packet);

	return 1;
}
