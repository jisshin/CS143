#include "../include/retrieve_network_info.hpp"
#include "../include/networkmanager.hpp"
#include "../lib/json/reader.h"
#include "../lib/json/value.h"
#include <string>


public string link_ids[];
public int link_rates[];
public int link_delays[];
public int link_buffers[];

public string flow_ids[];
public string flow_srcs[];
public string flow_dests[];
public int data_amts[];
public int flow_starts[];

void RetrieveNetworkInfo::setNetworkInfo(string file_name)
{
  Json::Value file;
  Json::Reader reader;

  bool parsingSuccessful = reader.parse(file_name, file);

  if ( !parsingSuccessful )
  {
    // report to the user the failure and their locations in the document.
    std::cout  << "Failed to parse configuration\n"
               << reader.getFormattedErrorMessages();
    return;
  }
  Json::Value links = file["Links"];
  Json::Value flows = file["Flows"];

  for (int i = 0; i < links.size(); i++){
    link_ids[i] = links[i]["link_id"].asString();
    link_rates[i] = links[i]["link_rate"].asInt(); //check if exists
    link_delays[i] = link[i]["link_delay"].asInt();
    link_buffers[i] = link[i]["link_buffer"].asInt();


  }

  for (int i = 0; i < flows.size(); i++){
    flow_ids[i] = flow[i]["flow_id"].asString();
    flow_srcs[i] = flow[i]["flow_src"].asString();
    flow_dests[i] = flow[i]["flow_dest"].asString();
    data_amts = flow[i]["data_amt"].asInt();
    flow_starts = flow[i]["flow_start"].asFloat(); // CHeck if exists
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
