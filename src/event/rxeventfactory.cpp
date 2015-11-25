#include "../../include/event/rxeventfactory.hpp"
#include "../../include/event/rxackevent.hpp"
#include "../../include/event/rxendevent.hpp"
#include "../../include/event/rxfwdevent.hpp"
#include "../../include/event/rxrouteevent.hpp"
#include "../../include/packet.hpp"
#include "../../include/link.hpp"
#include "../../include/node.hpp"

RxEvent* RxEventFactory::makeRxEvent(Link *pLink, Node *pNode, Packet *pPkt)
{

  if (pPkt->packet_type == SRC_PACKET)
    if (pPkt->packet_dest == (std::string)*pNode)
      return new RxAckEvent(pLink, pNode, pPkt);

  if (pPkt->packet_type == ACK_PACKET)
      return new RxEndEvent(pLink, pNode, pPkt);

  if (pPkt->packet_type == ROUT_PACKET)
	if (pPkt->packet_dest == (std::string)*pNode)
	  return new RxRouteEvent(pLink, pNode, pPkt);
	  
  return new RxFwdEvent(pLink, pNode, pPkt);
}
