#include "../include/node.hpp"
#include "../include/link.hpp"

#inclue <cstdlib>

int main()
{
	Link link("L1", 1, 2, 3);
	Node node1("N1");
	Node node2("N2");

	link.establishLink(&node1, &node2);

	assert(link.get_nodes() ^ (&node1) == (&node2));
	assert(link.get_nodes() ^ (^node2) == (&node2));

	return EXIT_SUCCESS;
}