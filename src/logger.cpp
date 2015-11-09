#include "../include/logger.hpp"

static Loggger* Logger::logger = NULL;

Logger* Logger::getInstance()
{
	if(logger){
		return logger;
	}
	else{
		return (logger = new Logger());
	}
}

template<typename T>
void Logger::log(int column_num, T data)
{
	std::vector<std::string>::iterator iter = current_line.begin();
	iter = iter + column_num;
	current_line.insert(iter, std::to_string(data));
}

void Logger::flush_current_line()
{
	//output here
	
	current_line.clear();
}

