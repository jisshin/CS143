#include "../../include/event/rxendevent.hpp"
#include "../../include/event/txsrcevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/flow.hpp"
#include "../../include/link.hpp"
#include "../../include/packet.hpp"
#include "../../include/node.hpp"
#include "../../include/common.hpp"


int RxEndEvent::handleEvent()
{
	rx_link->popPacket(rx_packet);
	rx_node->receivePacket(rx_packet);

#ifdef CHECK_DROP
	std::cout << "receive ack " << rx_packet->packet_seq_id\
		<<std::endl;
#endif//DEBUG


	NetworkManager* nm = NetworkManager::getInstance();
	Flow* rx_flow = nm->getFlow(rx_packet->packet_flow_id);
	std::cout << "got ack : "<< rx_packet->packet_seq_id << std::endl;
	rx_flow->receiveAckAndGenRx(rx_packet);
	delete rx_packet;
	return 1;
}
