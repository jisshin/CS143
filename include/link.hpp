
#ifndef LINK_H
#define LINK_H

class Link {
public:
	Link(int rate, int delay, int buffer_size)\
	: link_rate(rate), \
	  link_delay(delay), \
	  link_buffer_size(buffer_size)
	{}

	int getRate() { return link_rate; }
	int getDelay() { return link_delay; }
	int getBufferSize() { return link_buffer_size; }

	int putPacket() {}

private:
	int link_rate;
	int link_delay;
	int link_buffer_size;
};

#endif //LINK_H
