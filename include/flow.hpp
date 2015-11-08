#ifndef FLOW_H
#define FLOW_H

#include <string>

//TODO move status constant to a ENUM
#define PACKET_DROPPED = 0;

class Packet;

class Flow {
public:
	Flow(std::string id, std::string src, std::string dest, int data_amt)\
	: flow_id(id), \
	  flow_src(src), \
	  flow_dest(dest), \
	  flow_data_amt(data_amt){};

	Packet* genNextPacket();
	void update_flow(int id, int status);

	std::string getSrc() { return flow_src; }
	std::string getDest() { return flow_dest; }
	int getDataAmt() { return flow_data_amt; }
	void setDataAmt(int new_data_amt) { flow_data_amt = new_data_amt; }
	operator std::string() { return flow_id; }

private:
	std::string flow_id;
	std::string flow_src;
	std::string flow_dest;
	int flow_data_amt;
	//next_id is just temporary packet id counter to test txevent
	int next_id = 0;


};



#endif //FLOW_H
