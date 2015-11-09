#include "../include/eventqueue.hpp"
#include "../include/event.hpp"
#include "../include/node.hpp"
#include "../include/flow.hpp"
#include "../include/event/txevent.hpp"
#include "../include/networkmanager.hpp"
#include <cassert>
using std::vector;
using std::string;

int main(){
	EventQueue* eventq = EventQueue::getInstance();
	NetworkManager* mgr = NetworkManager::getInstance();

	Node node1("N1");
	Node node2("N2");
	Flow flow1("F1", "N1", "N2",10);
	int result = mgr->registerFlow(flow1);
	assert(result == -1);

	mgr->registerFlow(string("flow1"),testflow1);

	TxEvent txevent1("node1",testflow1.genNextPacket());
	txevent1.time = 0.1;
	std::cout<<"push first tx event" << std::endl;
	eventq.push(&txevent1);

	// start looping untill queue empty
	while(!eventq.empty()){
		std::cout << "dequee" << std::endl;
		eventq.pop()->handleEvent();
	}
}
