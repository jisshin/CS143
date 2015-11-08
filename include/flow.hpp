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

	std::string getSrc() { return flow_src; }
	std::string getDest() { return flow_dest; }
	int getDataAmt() {return flow_data_amt; }
	void setDataAmt(int new_data_amt){ flow_data_amt = new_data_amt; }

private:
	std::string flow_src;
	std::string flow_dest;
	int flow_data_amt;
};

#endif //FLOW_H
