#ifndef COMMON_H
#define COMMON_H


#define LOGGER_OUTPUT "output/output.csv"

const double LOG_INTERVAL = 0.06;

const double ROUT_INTERVAL = 0.000001;
const double REST_INTERVAL = 5;

const double Gamma = 0.90;
const double alpha = 15;

enum TCPType {
	TCP_RENO_t, TCP_FAST_t
};





//#define DEBUG
//#define CHECK_DROP
//#define err_test
//#define JISOO
//#define DEBUG_FLOW "F1"

#include <cassert>

#endif //COMMON_H


