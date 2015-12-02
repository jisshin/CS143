#include "../../include/event/txsrcevent.hpp"
#include "../../include/event/tcpfastupdate.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/flow.hpp"

int TCPFastUpdate::handleEvent() {
	EventQueue::getInstance()->num_non_core--;

	
	return 1;
}


