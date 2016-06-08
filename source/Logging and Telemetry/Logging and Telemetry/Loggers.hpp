#ifndef _LOGGERS_HPP
#define _LOGGERS_HPP

#include <string>

//LogAdapter is an interface for writing strings
class LogAdapter {
public: 
	LogAdapter();
	
	virtual void write(const std::string& data) = 0;
};

//Console implementation of a LogAdapter
class ConsoleLogAdapter : public LogAdapter {
public:
	ConsoleLogAdapter();

	void write(const std::string &data) override;

};

//File implementation of a LogAdapter, write string of stream to file
class FileLogAdapter : public LogAdapter {
public: 
	FileLogAdapter(const std::string& filename);

	void write(const std::string& data) override;

private:
	std::string filename;
};

//Handle the reference to the LogAdapter
//A logger always uses a LogAdapter to write it's data.
class Logger {
public: 
	Logger(const LogAdapter &logAdapter);

private:
	LogAdapter logAdapter;
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

	DebugLogger(const LogAdapter& logAdapter);

	void Log(const Clock::TimeStamp &time, const LOG_TYPE &type, const std::string& massage);
};

//Telemetry implementation of a Logger. Gather data and write it to the adapter. 
class TelemetryLogger : Logger {
	TelemetryLogger(const LogAdapter&, const SharedObject<RobotStatus>&, const SharedObject<Map>&);

	void Log();
};

#endif _LOGGERS_HPP 

