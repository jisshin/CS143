#ifndef EVENT_TCPFASTUPDATE_H
#define EVENT_TCPFASTUPDATE_H

#include "../event.hpp"
#include "../eventqueue.hpp"

class TCPFast;
class Flow;

/**
 * TCPFastUpdate event implement Event class.
 * This represents the event that periodically update hte
 * window size for TCPFast algorithm.
 */
class TCPFastUpdate :public Event {
public:
	TCPFastUpdate(double t, TCPFast* tcp) : Event(t), fast(tcp)
	{}

	/**
	 * Update the window size and generate a source packet
	 * if there is a new window spot open.
	 */
	int handleEvent() override;

private:
	TCPFast* fast;

};

#endif /* EVENT_TCPFASTUPDATE_H */
