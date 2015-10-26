#ifndef LINK_H
#define LINK_H

class Link {
public:
	Link(char* ID, int link_rate, int link_delay, int link_buffer)\
	: m_ID(ID), \
	  m_link_rate(link_rate), \
	  m_link_delay(link_delay), \
	  m_link_buffer(link_buffer)
	{}

private:
	char* m_ID;
	int m_link_rate;
	int m_link_delay;
	int m_link_buffer;
};

#endif //LINK_H
