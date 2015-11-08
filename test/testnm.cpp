#include <cstdlib>
#include <string>

#include "link.hpp"
#include "networkmanager.hpp"
#include "flow.hpp"

int main()
{
	char x[] = "hello";
	Link link(1, 2, 3);
	Link link2(4, 5, 6);
	
	NetworkManager* instance = NetworkManager::getInstance();

	std::string str("L1");
	instance->registerLink(str, link);
	std::string str2("L12");
	instance->registerLink(str2, link2);

	std::string str3("L12");
	Link* l1 = instance->getLink(str3);
	printf("%d", l1->link_rate);
	return EXIT_SUCCESS;
}
