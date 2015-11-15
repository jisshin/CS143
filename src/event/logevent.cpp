#include "../include/networkmanager.hpp"
#include "../include/eventqueue.hpp"
#include "../include/node.hpp"
#include "../include/link.hpp"
#include "../include/flow.hpp"
#include "../include/logger.hpp"

int LogEvent::handleEvent()
{
  NetworkManager* nm = NetworkManager::getInstance();
  EventQueue* eq = EventQueue::getInstance();

  Link* link = nm->resetLinkIterator();
  Flow* flow = nm->resetFlowIterator();
  Node* node = nm->resetNodeIterator();

  while(link != NULL)
  {
    logData(link);
    link = nm->getNextLinkIterator();
  }

  while(flow != NULL)
  {
    logData(flow);
    flow = nm->getNextFlowIterator();
  }

  while(node != NULL)
  {
    if (node->getAdjNodes()->size() == 1)
    {
      //there is only one node connected to this node
      //thus this is host. we are interested in logging
      //data for only host.
      logData(node);
    }
    node = nm->getNextNodeIterator();
  }

  if (!commonIsSimOver())
    eq->push(new LogEvent());
}

int LogEvent::logData(Link* link)
{
  Logger* logger = Logger::getInstance();
  logger->prepare();

  logger->log_str((std::string) *link);
  logger->log_num(getBufOccupancy(link));
  logger->log_num(getPacketLoss(link));
  logger->log_num(getFlowRate(link));

  logger->flush_current_line();
}

int LogEvent::logData(Flow* flow)
{
  //TODO flow related logging
}

int LogEvent::logData(Node* node)
{
  //TODO host related logging
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

int LogEvent::getPacketLoss(Link* link)
{
  int ret = link->num_packet_drop;
  link->num_packet_drop = 0;
  return ret;
}

int LogEvent::getFlowRate(Link* link)
{
  int ret = link->packet_thru;
  link->packet_thru = 0;
  return ret;
}
