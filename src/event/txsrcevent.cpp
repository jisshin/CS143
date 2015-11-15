#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/packet.hpp"
#include "../../include/flow.hpp"

#include <cassert>

TxSrcEvent::TxSrcEvent(Packet* pPkt) : TxEvent(pPkt, NULL)
{
  NetworkManager* nm = NetworkManager::getInstance();
  tx_node = nm->getNode(pPkt->packet_src);
}

int TxSrcEvent::handleEvent()
{
  //this can not happen due to constructor, but for debug
  //purpose
  assert(tx_packet->packet_src == *tx_node);

  TxEvent::handleEvent();

  // if this is the first tx event from source,
  // check if next packet is available from flow, generate next_tx event regardless the status of
  // transmit;
  NetworkManager* nm = NetworkManager::getInstance();
  EventQueue* eventq = EventQueue::getInstance();

  Flow* tx_flow = nm->getFlow(tx_packet->packet_flow_id);
  Packet* nxt_tx_pkt = tx_flow->genNextPacketFromTx();
  if (nxt_tx_pkt != NULL){
    TxEvent* next_tx = new TxEvent(nxt_tx_pkt, tx_node);
    // this time should be TCP dependent
    next_tx->time = time + tx_flow->getTxDelay();
    eventq->push(next_tx);
  }
}
