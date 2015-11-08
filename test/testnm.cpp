#include <cstdlib>
#include <string>

#ifndef _MSC_VER
#include "../include/link.hpp"
#include "../include/networkmanager.hpp"
#include "../include/flow.hpp"
#else
#include "link.hpp"
#include "networkmanager.hpp"
#include "flow.hpp"
#endif

#include <cassert>

int main()
{
	char x[] = "hello";
	Link link(1, 2, 3);
	Link link2(4, 5, 6);
	
	NetworkManager* instance = NetworkManager::getInstance();

	Flow flow("H1", "H2", 30);
	int result = instance->registerFlow("F1", flow);
	assert(result == -1);

	std::string str("L1");
	instance->registerLink(str, link);
	std::string str2("L12");
	instance->registerLink(str2, link2);

	std::string str3("L12");
	assert(instance->getLink(str3)->getRate() == 4);


	printf("Test Success - network manager\n");
	return EXIT_SUCCESS;
}
