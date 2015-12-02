#include "../include/retrieve_network_info.hpp"
#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/logger.hpp"
#include "../lib/json/json.h"
#include "../lib/json/reader.h"
#include "../lib/json/value.h"
#include "../include/flow.hpp"
#include "../include/link.hpp"
#include "../include/packet.hpp"
#include "../include/node.hpp"
#include "../include/event/txsrcevent.hpp"
#include "../include/event/logevent.hpp"
#include "../include/common.hpp"
#include "../include/tcpalgorithm/tcpreno.hpp"
#include "../include/tcpalgorithm.hpp"

#include <iostream>
#include <fstream>

#include <cstdlib>
#include <vector>

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
    link_rates.push_back(links[i]["link_rate"].asDouble());
    link_delays.push_back(links[i]["link_delay"].asDouble());
    link_buffers.push_back(links[i]["link_buffer"].asInt());
  }

  for (int i = 0; i < flow_no; i++){
    flow_ids.push_back(flows[i]["flow_id"].asString());
    flow_srcs.push_back(flows[i]["flow_src"].asString());
    flow_dests.push_back(flows[i]["flow_dest"].asString());
    data_amts.push_back(flows[i]["data_amt"].asInt());
    flow_starts.push_back(flows[i]["flow_start"].asDouble());
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

int RetrieveNetworkInfo::createNetwork(string method)
{

  NetworkManager *manager = NetworkManager::getInstance();

  // register links
  for (int i = 0; i < link_no; i++){
    Link link(link_ids[i], link_rates[i] * 1000000, link_delays[i] * .001, link_buffers[i] * 1000);
    manager->registerLink(link);
  }

  for (int i = 0; i < node_no; i++){
    Node node(all_nodes[i]);
    manager->registerNode(node);
  }

  for (int i = 0; i < connection_no; i++){
    manager->connectLink(c_link[i], c_node1[i], c_node2[i]);

  }
  EventQueue* eq = EventQueue::getInstance();
  // register flows
  for (int i = 0; i < flow_no; i++){
    Flow flow(flow_ids[i], flow_srcs[i], flow_dests[i], data_amts[i] * 1000000);
    TCPAlgorithm* alg = NULL;
    if(method == "Reno"){
    	alg = new TCPReno();
    }
    else if(method == "Fast"){
      //alg = new TCPFast
    }
    else{
    	std::cout << "undefined algorithm type no." << std::endl;
    	alg = new TCPReno();
    	// set to some default
    }
    flow.setTCPStrategy(alg);
    manager->registerFlow(flow);

    Packet* init_tx_packet = flow.genNextPacketFromTx();
	  TxSrcEvent *init_tx = new TxSrcEvent(init_tx_packet);
    init_tx->time = flow_starts[i];
  	eq->push(init_tx);

  }

  eq->run();

  Logger * logger = Logger::getInstance();
	delete logger;

	return EXIT_SUCCESS;

}
