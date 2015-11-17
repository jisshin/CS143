#include "../../include/event/rxeventfactory.hpp"
#include "../../include/event/rxackevent.hpp"
#include "../../include/event/rxendevent.hpp"
#include "../../include/event/rxfwdevent.hpp"
#include "../../include/packet.hpp"
#include "../../include/link.hpp"
#include "../../include/node.hpp"

RxEvent* RxEventFactory::makeRxEvent(Link *pLink, Node *pNode)
{
  Packet* rpkt = pLink->lastPacket();

  if (rpkt->packet_type == SRC_PACKET)
    if (rpkt->packet_dest == (std::string)*pNode)
      return new RxAckEvent(pLink, pNode);

  if (rpkt->packet_type == ACK_PACKET)
      return new RxEndEvent(pLink, pNode);

  if (rpkt->packet_type == ROUT_PACKET)
	if (rpkt->packet_dest == (std::string)*pNode)
	  return new RxRouteEvent(pLink, pNode);
	  
  return new RxFwdEvent(pLink, pNode);
}
