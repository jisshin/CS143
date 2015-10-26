#include <cstdlib>
#include "link.hpp"
#include "networkmanager.hpp"
#include "flow.hpp"

int main()
{
	char x[] = "hello";
	Link link(1, 2, 3);
	
	NetworkManager* instance = NetworkManager::getInstance();

	char str[3] = "L1";
	instance->registerLink(str, link);

	char str2[3] = "L1";
	Link* l1 = instance->getLink(str2);
	printf("%d", l1->link_rate);
	return EXIT_SUCCESS;
}
