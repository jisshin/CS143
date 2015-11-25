#include "../../include/event/tcptimeoutevent.hpp"
#include "../../include/flow.hpp"

int TCPTimeOutEvent::handleEvent(){
	if (src_flow->checkTimeout(tx_packet_id)){
		src_flow->getTCPStrategy()->rx_timeout();
	}
	return 1;
}


