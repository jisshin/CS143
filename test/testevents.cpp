#include "event/rxevent.hpp"

#include <cassert>

int main()
{
	RxEvent rxevent("H1", NULL);

	assert(rxevent.event_owner == "H1");

	return 1;
}