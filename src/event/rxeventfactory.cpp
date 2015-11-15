#include "../include/event/rxeventfactory.hpp"
#include "../include/packet.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"

RxEvent* RxEventFactory::makeRxEvent(Link *pLink, Node *pNode)
{
  Packet* rpkt = pLink->peekPacket();

  if (rpkt->packet_type == SRC_PACKET)
    if (rpkt->packet_dest == *pNode)
      return new RxAckEvent(pLink, pNode);

  if (rpkt->packet_type == ACK_PACKET)
      return new RxEndEvent(pLink, pNode);

  return new RxEvent(pLink, pNode);
}
