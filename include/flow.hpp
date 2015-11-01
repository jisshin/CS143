#ifndef FLOW_H
#define FLOW_H

#include <string>

class Flow {
public:
	Flow(std::string src, std::string dest, int data_amt)\
	: flow_src(src), \
	  flow_dest(dest), \
	  flow_data_amt(data_amt)
	{}

	std::string flow_src;
	std::string flow_dest;
	int flow_data_amt;
	double flow_start_time;
};

#endif //FLOW_H
