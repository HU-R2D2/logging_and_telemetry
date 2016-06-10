#include "../include/Loggers.hpp"
#include <string>
#include <fstream>
#include <iostream>

void LogAdapter::write(const std::string& data) {}

void ConsoleLogAdapter::write(const std::string &data) {
	std::cout << data << std::endl;
}

FileLogAdapter::FileLogAdapter(const std::string &filename) :
	filename(filename)
{
	fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
}

void FileLogAdapter::write(const std::string& data) {
	fs << data << std::endl;
}

Logger::Logger(LogAdapter& logAdapter):
	logAdapter(logAdapter)
{}

DebugLogger::DebugLogger(LogAdapter& logAdapter):
	Logger(logAdapter)
{}

inline const char* DebugLogger::ToString(LOG_TYPE t) {
	switch (t) {
		case LOG_TYPE::VERBOSE: return "VERBOSE";
		case LOG_TYPE::DEBUG:	return "DEBUG";
		case LOG_TYPE::INFO: return "INFO";
		case LOG_TYPE::WARNING: return "WARNING";
		case LOG_TYPE::ERROR: return "ERROR";
	}
}


void DebugLogger::log(const std::string &time, const LOG_TYPE &type, const std::string& massage) {
	logAdapter.write("[" + time + "] " + "[" + ToString(type) + "] " + ": " + massage);
}
/*
TelemetryLogger::TelemetryLogger(const LogAdapter&, const SharedObject<RobotStatus>&, const SharedObject<Map>&):
{}

void TelemetryLogger::Log() {

}
*/
