#ifndef _MSC_VER
#include "../include/node.hpp"
#include "../include/link.hpp"
#include "../include/packet.hpp"
#else
#include "node.hpp"
#include "link.hpp"
#include "packet.hpp"
#endif

#include <stdint.h>
#include <cassert>
#include <cstdlib>

int main()
{
	Link link("L1", 1, 2, 3);
	Node node1("N1");
	Node node2("N2");

	Packet packet("1", "1", "1", 1);

	link.establishLink(&node1, &node2);
	node1.establishLink(&link);
	node2.establishLink(&link);

	assert(link.get_other_node(&node1) == &node2);
	assert(link.get_other_node(&node2) == &node1);

	uintptr_t node = NULL;
	node1.transmitPacket(&packet, &node);

	assert((Node *)node == &node2);
	printf("Test success - Link & node\n");

	return EXIT_SUCCESS;
}