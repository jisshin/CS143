#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>

class Logger{
	public:
		static Logger* getInstance();

		template<typename T>
		void log(int column_num, T data);

		void flush_current_line();

	private:
		std::vector<std::string> current_line;
};
#endif