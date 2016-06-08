#include "Loggers.hpp"
#include <string>

LogAdapter::LogAdapter(){

}

void LogAdapter::write(const std::string& data) {

}

ConsoleLogAdapter::ConsoleLogAdapter()
{}

void ConsoleLogAdapter::write(const std::string &data) {

}

FileLogAdapter::FileLogAdapter(const std::string &filename) :
	filename(filename)
{}

void FileLogAdapter::write(const std::string& filename) {

}

Logger::Logger(const LogAdapter& logAdapter):
	logAdapter(logAdapter)
{}

DebugLogger::DebugLogger(const LogAdapter& logAdapter):
	Logger(logAdapter)
{

}

void DebugLogger::Log(const Clock::TimeStamp &time, const LOG_TYPE &type, const std::string& massage) {

}

TelemetryLogger::TelemetryLogger(const LogAdapter&, const SharedObject<RobotStatus>&, const SharedObject<Map>&):
{}

void TelemetryLogger::Log() {

}

