#include "../include/retrieve_network_info.hpp"
#include "../include/networkmanager.hpp"
//#include "../lib/include/json/json.h"
#include "../lib/json/json.h"
#include "../lib/json/reader.h"
#include "../lib/json/value.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::vector;
using std::string;
using std::cout;

std::vector<string> link_ids;
std::vector<double> link_rates;
std::vector<double> link_delays;
std::vector<double> link_buffers;

std::vector<string> flow_ids;
std::vector<string> flow_srcs;
std::vector<string> flow_dests;
std::vector<double> data_amts;
std::vector<double> flow_starts;


void RetrieveNetworkInfo::setNetworkInfo(string file_name)
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
    return;
  }
  Json::Value links = root["Links"];
  Json::Value flows = root["Flows"];

  for (int i = 0; i < links.size(); i++){
    link_ids.push_back(links[i]["link_id"].asString());
    link_rates.push_back(links[i]["link_rate"].asDouble()); //check if exists
    link_delays.push_back(links[i]["link_delay"].asDouble());
    link_buffers.push_back(links[i]["link_buffer"].asDouble());


  }

  for (int i = 0; i < flows.size(); i++){
    flow_ids.push_back(flows[i]["flow_id"].asString());
    flow_srcs.push_back(flows[i]["flow_src"].asString());
    flow_dests.push_back(flows[i]["flow_dest"].asString());
    data_amts.push_back(flows[i]["data_amt"].asDouble());
    flow_starts.push_back(flows[i]["flow_start"].asDouble()); // CHeck if exists
  }


  return;
}

/*int RetrieveNetworkInfo::createFlow()
{
  for (int i = 0; i < flows.size(); i++){
    Flow flow = new Flow(flow_srcs[i], flow_dests[i], data_amts[i]);
    registerFlow(flow_ids[i], flow);
  }
  return 1;
}

int RetrieveNetworkInfo::createLink()
{
  for (int i = 0; i < links.size(); i++){
    Link link = new Link(link_rates[i], link_delays[i], link_buffers[i]);
    registerLink(link_ids[i], link);
  }
  return 1;
}*/
