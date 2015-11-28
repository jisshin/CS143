#include "../../include/event/tcptimeoutevent.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/flow.hpp"

int TCPTimeOutEvent::handleEvent(){
	EventQueue::getInstance()->num_non_core--;
	src_flow->checkTimeout(tx_packet_id);
	return 1;
}


