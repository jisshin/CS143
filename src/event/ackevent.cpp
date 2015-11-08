#include "../../include/event/ackevent.hpp"
#include <iostream>

int AckEvent::handleEvent(){
	std::cout<<"Handle ACK event"<<std::endl;
	return 0;
}

