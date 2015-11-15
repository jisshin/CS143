#include "../include/event/rxevent.hpp"
#include "../include/link.hpp"
#include "../include/node.hpp"
#include <cassert>

int main()
{
	Link link("L1", 30, 30, 30);
	Node node("H1");
	RxEvent rxevent(&link, &node);

	return 1;
}