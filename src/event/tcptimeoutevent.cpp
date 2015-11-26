#include "../../include/event/tcptimeoutevent.hpp"
#include "../../include/flow.hpp"

int TCPTimeOutEvent::handleEvent(){
	src_flow->checkTimeout(tx_packet_id);
	return 1;
}


