#include "../../include/event/rxendevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/flow.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"

int RxEndEvent::handleEvent()
{
  #ifdef DEBUG
  		std::cout<<"rxevent: receive ack packet " << rx_packet->id\
  				<<std::endl;
  #endif//DEBUG

  RxEvent::handleEvent();

  NetworkManager* nm = NetworkManager::getInstance();
  Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);
	rx_flow->receive_ack(rx_packet->id);
	// Check if suppose to send out new src packet
	Packet* new_src_packet = rx_flow->genNextPacketFromRx();
	if(new_src_packet != NULL){
		TxEvent* next_tx = new TxEvent(new_src_packet, rx_node);
		next_tx->time = time + rx_flow->getTxDelay();
    EventQueue* eventq = EventQueue::getInstance();
		eventq->push(next_tx);
	}

	return 1;
}
