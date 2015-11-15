#include "../include/networkmanager.hpp"
#include "../include/node.hpp"
#include "../include/link.hpp"
#include "../include/flow.hpp"
#include "../include/logger.hpp"

int LogEvent::handleEvent()
{
  NetworkManager* nm = NetworkManager::getInstance();

  Link* link = nm->resetLinkIterator();

  while(link != NULL)
  {
    logData(link);
    link = nm->getNextLinkIterator();
  }

  Flow* flow = nm->resetFlowIterator();

  while(flow != NULL)
  {
    logData(flow);
    flow = nm->getNextFlowIterator();
  }

  Node* node = nm->resetNodeIterator();

  while(node != NULL)
  {
    logData(node);
    node = nm->getNextNodeIterator();
  }

  //add next event
}

int LogEvent::logData(Link* link)
{
  Logger* logger = Logger::getInstance();
  logger->prepare();

  logger->log_str((std::string) *link);
  logger->log_num(getBufOccupancy(link));
  logger->log_num(getPacketLoss(link));

  logger->flush_current_line();
}

int LogEvent::logData(Flow* flow)
{

}

int LogEvent::logData(Node* node)
{

}

int LogEvent::getBufOccupancy(Link* link)
{
  return (link->cur_buffer_size)/(link->max_buffer_size);
}

int LogEvent::getPacketLoss(Link* link)
{
  int ret = link->num_packet_drop;
  link->num_packet_drop = 0;
  return ret;
}
