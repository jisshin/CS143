/**
* Checks the functionality of retrieving network info.
*/

#include "../include/retrieve_network_info.hpp"


#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "enter json file name" << std::endl;
		return 0;
	}

	RetrieveNetworkInfo retrieve;

	if (retrieve.setNetworkInfo(argv[1])) {
		retrieve.createNetwork();
	}
	return 0;
}


