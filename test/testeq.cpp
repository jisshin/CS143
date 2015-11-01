#include "../include/eventqueue.hpp"

#include <cstdlib>

int main()
{
	EventQueue event = EventQueue::get_instance();
	return EXIT_SUCCESS;
}