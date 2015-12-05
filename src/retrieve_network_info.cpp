#include "../include/retrieve_network_info.hpp"
#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/logger.hpp"
#include "../include/event/logevent.hpp"
#include "json/json.h"
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
  std::ifstream file(file_name);
  if (!file) {
     cerr << "Open " << file_name << " failed" << std::endl;
     return 0;
   }
  Json::Value root;
  Json::Reader reader;

  bool parsingSuccessful = reader.parse(file, root);

  if ( !parsingSuccessful )
  {
    // report to the user the failure and their locations in the document.
    std::cout  << "Failed to parse configuration\n"
               << reader.getFormattedErrorMessages();
    return 0;
  }
  log_interval = root["log_interval"].asDouble();
  network_complexity = root["network_complexity"].asInt();
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
    flow_tcp.push_back(flows[i]["flow_tcp"].asInt());
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
  EventQueue* eq = EventQueue::getInstance();

  manager->initNetworkSim(log_interval, network_complexity);

  // register links
  for (int i = 0; i < link_no; i++){
    Link* myLink = new Link(link_ids[i], link_rates[i] * 1000000, link_delays[i] * .001, link_buffers[i] * 1000);
    manager->registerLink(*myLink);
  }

  // register nodes
  for (int i = 0; i < node_no; i++){
    Node* myNode = new Node(all_nodes[i]);
    manager->registerNode(*myNode);
  }

  // register links
  for (int i = 0; i < connection_no; i++){
    manager->connectLink(c_link[i], c_node1[i], c_node2[i]);
  }

  // register flows
  for (int i = 0; i < flow_no; i++){
    Flow* myFlow= new Flow(flow_ids[i], \
    		flow_srcs[i], flow_dests[i], data_amts[i] * 1000000, \
			flow_tcp[i], flow_starts[i]);
    manager->registerFlow(*myFlow);
  }

  eq->run();

  Logger * logger = Logger::getInstance();
	delete logger;

	return EXIT_SUCCESS;

}
