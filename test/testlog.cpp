#ifndef _MSC_VER
#include "../include/logger.hpp"
#else
#include "logger.hpp"
#endif

#include <iostream>
#include <fstream>

int main()
{
	Logger *log = Logger::getInstance();

	int i = 3;
	double j = 3.4;
	log->log_num(i);
	log->log_num(j);
	log->flush_current_line();
	log->log_num(3.5);
	log->log_num(3.45324);
	log->log_str("HELLO");
	log->log_str("03:HELLO");
	log->flush_current_line();
	return 1;
}