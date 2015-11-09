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
	int result = mgr->registerNode(node1);
	assert(result == -1);
	result = mgr->registerNode(node2);
	assert(result == -1);
	Flow flow1("F1", "N1", "N2",10);
	result = mgr->registerFlow(flow1);
	assert(result == -1);

	// connect links
	mgr->connectLink("L1", "N1", "N2");


	TxEvent txevent1("N1",flow1.genNextPacket());
	txevent1.time = 0.1;
	std::cout<<"Initialized first tx event"<< std::endl;
	eventq->push(&txevent1);

	// start looping until queue empty
	while(!eventq->empty()){
		eventq->pop()->handleEvent();
	}
}
