#include "../include/eventqueue.hpp"
#include "../include/event.hpp"
#include "../include/node.hpp"
#include "../include/flow.hpp"
#include "../include/event/txevent.hpp"
#include "../include/networkmanager.hpp"

using std::vector;
using std::string;

int main(){
	EventQueue eventq = EventQueue::get_instance();
	NetworkManager* mgr = NetworkManager::getInstance();
	Node* node1;
	Node* node2;
	Link* link1;
	vector<Node*>adj_n1;
	vector<Node*>adj_n2;
	vector<Link*>adj_l1;
	vector<Link*>adj_l2;
	adj_n1.push_back(node1);
	adj_n2.push_back(node2);
	adj_l1.push_back(link1);
	adj_l2.push_back(link1);

	node1 = new Node(adj_n1, adj_l1);
	node2 = new Node(adj_n2, adj_l2);
	Flow testflow1("node1","node2",10);
	mgr->registerNode(string("node1"), *node1);

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
