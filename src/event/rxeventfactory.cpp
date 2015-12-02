#include "../../include/event/rxeventfactory.hpp"
#include "../../include/event/rxackevent.hpp"
#include "../../include/event/rxendevent.hpp"
#include "../../include/event/rxfwdevent.hpp"
#include "../../include/event/rxrouteevent.hpp"
#include "../../include/packet.hpp"
#include "../../include/link.hpp"
#include "../../include/node.hpp"

RxEvent* RxEventFactory::makeRxEvent(double time, Link *pLink, Node *pNode, Packet *pPkt)
{

	if (pPkt->packet_dest == (std::string)*pNode)
	{
		if (pPkt->packet_type == SRC_PACKET)
			return new RxAckEvent(time, pLink, pNode, pPkt);

		//what is going on with this packet?
		if (pPkt->packet_type == ACK_PACKET)
			return new RxEndEvent(time, pLink, pNode, pPkt);

		if (pPkt->packet_type == ROUT_PACKET)
			return new RxRouteEvent(time, pLink, pNode, pPkt);
	}
	else
	{
		return new RxFwdEvent(time, pLink, pNode, pPkt);
	}

}
