#include "../include/logger.hpp"


Logger* Logger::logger = NULL;

Logger* Logger::getInstance()
{
	if (logger) {
		return logger;
	}
	else {
		return (logger = new Logger(LOGGER_OUTPUT));
	}
}

Logger::Logger(std::string file_dir)
{
	file.open(file_dir);
}

Logger::~Logger()
{
	flush_current_line();
	file.close();
}

void Logger::flush_current_line()
{
	std::string output_str = "";
	
	for (int i = 0; i < current_line.size(); i++)
	{
		output_str += current_line[i];
		output_str += ",";
	}
	output_str += "\n";

	file << output_str;
	current_line.clear();
}

