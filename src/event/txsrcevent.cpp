#include "../../include/event/txsrcevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/packet.hpp"
#include "../../include/flow.hpp"
#include "../../include/common.hpp"


TxSrcEvent::TxSrcEvent(double t, Packet* pPkt) : TxEvent(t, pPkt, NULL)
{
	NetworkManager* nm = NetworkManager::getInstance();
	tx_node = nm->getNode(pPkt->packet_src);
}

int TxSrcEvent::handleEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();
	Flow* tx_flow = nm->getFlow(tx_packet->packet_flow_id);
	commonTransmit(tx_node, tx_packet);
	tx_flow->sendSrcAndGenTx(tx_packet);		
	
	return 1;
}
