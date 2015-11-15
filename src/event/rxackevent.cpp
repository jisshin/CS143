#include "../../include/event/rxackevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/flow.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"

int RxAckEvent::handleEvent()
{
  #ifdef DEBUG
  	std::cout<<"rxevent: receive src packet " << rx_packet->id\
  	<<std::endl;
  #endif//DEBUG

  RxEvent::handleEvent();

  NetworkManager* nm = NetworkManager::getInstance();
	Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);

	// convert to ack packet
	Packet* ack_packet = rx_flow->genAckPacket(rx_packet);
	// And transmit back to sender
  return commonTransmit(rx_node, ack_packet);
}
