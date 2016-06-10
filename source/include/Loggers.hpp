#ifndef _LOGGERS_HPP
#define _LOGGERS_HPP

#include <string>
#include <fstream>

//LogAdapter is an interface for writing strings
class LogAdapter {
public: 	
	virtual void write(const std::string& data) = 0;
};

//Console implementation of a LogAdapter
class ConsoleLogAdapter : public LogAdapter {
public:
	void write(const std::string &data) override;
};

//File implementation of a LogAdapter, write string of stream to file
class FileLogAdapter : public LogAdapter {
public: 
	FileLogAdapter(const std::string& filename);

	void write(const std::string& data) override;

private:
	std::fstream fs;
	std::string filename;
};

//Handle the reference to the LogAdapter
//A logger always uses a LogAdapter to write it's data.
class Logger {
public: 
	Logger(LogAdapter &logAdapter);
	LogAdapter & logAdapter;
};

// Debug implementation of a Logger. Handles formatting user debug log. 
class DebugLogger : public Logger {
public: 
	enum class LOG_TYPE {
		VERBOSE,
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

	DebugLogger(LogAdapter& logAdapter);

	void log(const std::string& time, const LOG_TYPE &type, const std::string& massage); // const std::string& time => const Clock::TimeStamp& time 

private:
	inline const char* ToString(LOG_TYPE t);
};
/*
//Telemetry implementation of a Logger. Gather data and write it to the adapter. 
class TelemetryLogger : Logger {
	TelemetryLogger(const LogAdapter&, const SharedObject<RobotStatus>&, const SharedObject<Map>&);

	void log();
};
*/
#endif