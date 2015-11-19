#include "../include/retrieve_network_info.hpp"
#include "../include/networkmanager.hpp"
#include "../include/event/txevent.hpp"
#include "../include/eventqueue.hpp"
//#include "../lib/include/json/json.h"
#include "../lib/json/json.h"
#include "../lib/json/reader.h"
#include "../lib/json/value.h"
#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/packet.hpp"
#include "../include/node.hpp"
#include "../include/tcpalgorithm/tcpreno.hpp"
#include "../include/tcpalgorithm.hpp"

#include <iostream>
#include <fstream>

using std::vector;
using std::string;
using std::cout;


int RetrieveNetworkInfo::setNetworkInfo(string file_name)
{
  std::ifstream file(file_name, std::ifstream::binary);
  Json::Value root;
  Json::Reader reader;

  bool parsingSuccessful = reader.parse(file, root);

  if ( !parsingSuccessful )
  {
    // report to the user the failure and their locations in the document.
    std::cout  << "Failed to parse configuration\n"
               << reader.getFormattedErrorMessages();
    return -1;
  }
  Json::Value links = root["Links"];
  Json::Value flows = root["Flows"];
  Json::Value connections = root["Connections"];
  Json::Value packets = root["Packets"];
  Json::Value nodes = root["Nodes"];
  flow_no = flows.size();
  link_no = links.size();
  connection_no = connections.size();
  packet_no = packets.size();
  node_no = nodes.size();
  // get all link info
  for (int i = 0; i < link_no; i++){
    link_ids.push_back(links[i]["link_id"].asString());
    link_rates.push_back(links[i]["link_rate"].asDouble()); //check if exists
    link_delays.push_back(links[i]["link_delay"].asDouble());
    link_buffers.push_back(links[i]["link_buffer"].asDouble());
  }

  for (int i = 0; i < flow_no; i++){
    flow_ids.push_back(flows[i]["flow_id"].asString());
    flow_srcs.push_back(flows[i]["flow_src"].asString());
    flow_dests.push_back(flows[i]["flow_dest"].asString());
    data_amts.push_back(flows[i]["data_amt"].asDouble());
    flow_starts.push_back(flows[i]["flow_start"].asDouble()); // CHeck if exists
    flow_alg.push_back(flows[i]["flow_alg"].asInt());
  }

  for (int i = 0; i < connection_no; i++){
    c_link.push_back(connections[i][0].asString());
    c_node1.push_back(connections[i][1].asString());
    c_node2.push_back(connections[i][2].asString());

  }

  for (int i = 0; i < node_no; i++){
    all_nodes.push_back(nodes[i].asString());
  }

  return 1;
}

int RetrieveNetworkInfo::createNetwork()
{

  NetworkManager *manager = NetworkManager::getInstance();

  // register links
  for (int i = 0; i < link_no; i++){
    Link link(link_ids[i], link_rates[i], link_delays[i], link_buffers[i]);
    manager->registerLink(link);
  }

  for (int i = 0; i < node_no; i++){
    Node node(all_nodes[i]);
    manager->registerNode(node);
  }

  for (int i = 0; i < connection_no; i++){
    int result = manager->connectLink(c_link[i], c_node1[i], c_node2[i]);
    if (result == -1)
      return -1;
  }

  EventQueue* eq = EventQueue::getInstance();
  // register flows
  for (int i = 0; i < flow_no; i++){
    Flow* flow = new Flow(flow_ids[i], flow_srcs[i], flow_dests[i], data_amts[i]);
    TCPAlgorithm* flow_alg = NULL;
    if(flow_alg[i] == TCP_RENO_t){
    	flow_alg = new TCPReno();
    }
    else{
    	std::cout << "undefined algorithm type no." << std::endl;
    	flow_alg = new TCPReno();
    	// set to some default
    }
    flow->setTCPStrategy(flow_alg);
    int result = manager->registerFlow(*flow);
    if (result == -1) 
        return -1;

    Packet packet(flow_ids[i], flow_srcs[i], flow_dests[i], -1);
    TxEvent init_tx("H1", &packet);

  	eq->push(&init_tx);

  }
  
  eq->run();

	return EXIT_SUCCESS;

}
