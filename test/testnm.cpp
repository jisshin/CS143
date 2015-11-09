#include <cstdlib>
#include <string>

#ifndef _MSC_VER
#include "../include/link.hpp"
#include "../include/networkmanager.hpp"
#include "../include/flow.hpp"
#include "../include/node.hpp"
#else
#include "link.hpp"
#include "networkmanager.hpp"
#include "flow.hpp"
#include "node.hpp"
#endif

#include <cassert>

int main()
{
	char x[] = "hello";
	Link link("L1", 1, 2, 3);
	Link link2("L2", 4, 5, 6);
	
	NetworkManager* instance = NetworkManager::getInstance();

	Flow flow("F1", "H1", "H2", 30);
	int result = instance->registerFlow(flow);
	assert(result == -1);

	instance->registerLink(link);
	instance->registerLink(link2);

	assert(instance->getLink("L12") == NULL);

	Node n1("N1");
	Node n2("N2");
	instance->registerNode(n1);
	instance->registerNode(n2);

	instance->connectLink("L1", "N1", "N2");

	assert((std::string) *(instance->getLink("L1")->get_other_node(&n2)) == "N1");
	assert((std::string) *(instance->getLink("L1")->get_other_node(&n1)) == "N2");

	printf("Test Success - network manager\n");
	return EXIT_SUCCESS;
}
