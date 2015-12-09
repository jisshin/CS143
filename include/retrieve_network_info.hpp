#ifndef RETRIEVENETWORKINFO_H
#define RETRIEVENETWORKINFO_H

#include <string>
#include <vector>
using namespace std;

/**
 * This class process the input JSON file and create
 * the network strucuture.
 */
class RetrieveNetworkInfo {
public:
  RetrieveNetworkInfo(){}

  /**
   * Takes a valid Json file path and parse the JSON data
   */
  int setNetworkInfo(string file_name);

  /**
  * Creates data out of data obtained from input and
  * create network with NetworkManager
  */
  int createNetwork();

private:
	std::vector<string> link_ids;
	std::vector<double> link_rates;
	std::vector<double> link_delays;
	std::vector<int> link_buffers;

	std::vector<string> flow_ids;
	std::vector<string> flow_srcs;
	std::vector<string> flow_dests;
	std::vector<int> data_amts;
	std::vector<double> flow_starts;
	std::vector<int> flow_tcp;

	std::vector<string> all_nodes;

	std::vector<string> c_link;
	std::vector<string> c_node1;
	std::vector<string> c_node2;

	int flow_no;
	int link_no;
	int connection_no;
	int packet_no;
	int node_no;

	double log_interval;
	int network_complexity;

};
#endif //RETRIEVENETWORKINFO_H
