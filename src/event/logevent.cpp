#include "../../include/event/logevent.hpp"
#include "../../include/networkmanager.hpp"
#include "../../include/eventqueue.hpp"
#include "../../include/node.hpp"
#include "../../include/link.hpp"
#include "../../include/flow.hpp"
#include "../../include/logger.hpp"

int LogEvent::handleEvent()
{
	NetworkManager* nm = NetworkManager::getInstance();
	EventQueue* eq = EventQueue::getInstance();
	Logger* logger = Logger::getInstance();

	Link* link = nm->resetLinkIterator();
	Flow* flow = nm->resetFlowIterator();
	Node* node = nm->resetNodeIterator();

	logger->prepare();
	logger->log_num(time);

	while (link != NULL)
	{
		logData(link);
		link = nm->getNextLinkIterator();
	}

	while (flow != NULL)
	{
		logData(flow);
		flow = nm->getNextFlowIterator();
	}

	while (node != NULL)
	{
		if (node->getAdjLinks().size() == 1)
		{
			//there is only one node connected to this node
			//thus this is host. we are interested in logging
			//data for only host.
			logData(node);
		}
		node = nm->getNextNodeIterator();
	}

	logger->flush_current_line();

	return 1;
}

void LogEvent::logData(Link* link)
{
	Logger* logger = Logger::getInstance();
	logger->log_str((std::string) *link);
	logger->log_num(getBufOccupancy(link));
	logger->log_num(getPacketLoss(link));
	logger->log_num(getFlowRate(link));
}

void LogEvent::logData(Flow* flow)
{
	Logger* logger = Logger::getInstance();
	logger->log_str((std::string) *flow);
	logger->log_num(getSentRate(flow));
	logger->log_num(getRcvdRate(flow));
	logger->log_num(getPacketRTT(flow));
}

void LogEvent::logData(Node* node)
{
	Logger* logger = Logger::getInstance();
	logger->log_str((std::string) *node);
	logger->log_num(getSentRate(node));
	logger->log_num(getRcvdRate(node));
}

double LogEvent::getBufOccupancy(Link* link)
{
	return (link->cur_buf_size_in_byte) / (link->max_buf_size_in_byte);
}

int LogEvent::getPacketLoss(Link* link)
{
	double ret = link->num_packet_drop;
	link->num_packet_drop = 0;
	return (int)ret;
}

int LogEvent::getFlowRate(Link* link)
{
	double ret = link->packet_thru;
	link->packet_thru = 0;
	return (int)ret;
}

int LogEvent::getSentRate(Node* node)
{
	double ret = node->packet_sent;
	node->packet_sent = 0;
	return (int)ret;
}

int LogEvent::getRcvdRate(Node* node)
{
	double ret = node->packet_rcvd;
	node->packet_rcvd = 0;
	return (int)ret;
}

int LogEvent::getSentRate(Flow* flow)
{
	//double ret = flow->packet_sent;
	//flow->packet_sent = 0;
	//return (int)ret;
	return 0;
}

int LogEvent::getRcvdRate(Flow* flow)
{
	//double ret = flow->packet_rcvd;
	//flow->packet_rcvd = 0;
	//return (int)ret;
	return 0;
}

double LogEvent::getPacketRTT(Flow* flow)
{
	return 0;
}
