
#ifndef LINK_H
#define LINK_H

class Link {
public:
	Link(int rate, int delay, int buffer)\
	: link_rate(rate), \
	  link_delay(delay), \
	  link_buffer(buffer)
	{}

	int link_rate;
	int link_delay;
	int link_buffer;
};

#endif //LINK_H
