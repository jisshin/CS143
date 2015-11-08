#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/flow.hpp"
#include "../include/link.hpp"

#include <cstdlib>

int main()
{
	EventQueue eq = EventQueue::get_instance();
	Flow flow("H1", "H2", 20);

	eq.enqueue()
	return EXIT_SUCCESS;
}