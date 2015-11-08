#ifndef FLOW_H
#define FLOW_H

#include <string>

//TODO move status constant to a ENUM
#define PACKET_DROPPED = 0;

class Packet;

class Flow {
public:
	Flow(std::string src, std::string dest, int data_amt)\
	: flow_src(src), \
	  flow_dest(dest), \
	  flow_data_amt(data_amt){};


	std::string getSrc() { return flow_src; }
	std::string getDest() { return flow_dest; }
	int getDataAmt() {return flow_data_amt; }
	void setDataAmt(int new_data_amt){ flow_data_amt = new_data_amt; }

private:
	std::string flow_src;
	std::string flow_dest;
	int flow_data_amt;
	//next_id is just temporary packet id counter to test txevent
	int next_id = 0;
	//genNextPacket should be where the congestion 
	//algorithm is applied. 
	Packet* genNextPacket();
	void update_flow(int id, int status);

};



#endif //FLOW_H
