/*
 * node.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: jenniferlin
 */
#include "../include/node.hpp"

std::string Node::lookupRouting(std::string dest){
	return routing_table[dest];
}
