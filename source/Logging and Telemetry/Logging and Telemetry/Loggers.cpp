#include "Loggers.hpp"
#include <string>

LogAdapter::LogAdapter(const std::string& filename):
	filename(filename)
{}

void LogAdapter::write(const std::string& data) {

}

ConsoleLogAdapter::ConsoleLogAdapter(const std::string &filename) :
	LogAdapter(filename)
{}

void ConsoleLogAdapter::write(const std::string &data) {

}

