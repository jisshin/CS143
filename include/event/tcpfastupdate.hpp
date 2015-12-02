#ifndef EVENT_TCPFASTUPDATE_H
#define EVENT_TCPFASTUPDATE_H

#include "../event.hpp"
#include "../eventqueue.hpp"

class TCPFast;
class Flow;

class TCPFastUpdate :public Event {
public:
	TCPFastUpdate(double t, TCPFast* tcp) : Event(t), fast(tcp)
	{}

	int handleEvent() override;

private:
	TCPFast* fast;

};

#endif /* EVENT_TCPFASTUPDATE_H */
