#include "../../include/event/tcpfastupdate.hpp"
#include "../../include/tcpalgorithm/tcpfast.hpp"

int TCPFastUpdate::handleEvent() {

	fast->updateWindow();
	return 1;
}


