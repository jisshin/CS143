#include "../include/node.hpp"
#include "../include/link.hpp"

#include <stdint.h>
#include <cassert>
#include <cstdlib>

int main()
{
	Link link("L1", 1, 2, 3);
	Node node1("N1");
	Node node2("N2");

	link.establishLink(&node1, &node2);

	assert(link.get_other_node(&node1) == &node2);
	assert(link.get_other_node(&node2) == &node1);

	printf("Test success - Link & node\n");

	return EXIT_SUCCESS;
}