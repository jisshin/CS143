#ifndef FLOW_H
#define FLOW_H

class FlowInfo {
public:
	FlowInfo(){}
	char* flow_src;
	char* flow_dest;
	int data_amt;
	double flow_start;
};

class Flow {
public:
	Flow(char* ID, char* flow_src, char* flow_dest, int data_amt)\
	: m_ID(ID), \
	  m_flow_src(flow_src), \
	  m_flow_dest(flow_dest), \
	  m_data_amt(data_amt)
	{}

	void set_data_amt(int data_amt){ m_data_amt = data_amt; }
	int get_data_amt(){ return m_data_amt; }

private:
	char* m_ID;
	char* m_flow_src;
	char* m_flow_dest;
	int m_data_amt;
};

#endif //FLOW_H
