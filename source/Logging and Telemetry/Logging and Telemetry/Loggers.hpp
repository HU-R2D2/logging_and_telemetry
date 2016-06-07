#ifndef _LOGGERS_HPP
#define _LOGGERS_HPP

#include <string>

//LogAdapter is an interface for writing strings
class LogAdapter {
public: 
	LogAdapter(const std::string& filename);
	
	virtual void write(const std::string& data);

protected:
	std::string filename;
};

//Console implementation of a LogAdapter
class ConsoleLogAdapter : public LogAdapter {
public:
	ConsoleLogAdapter(const std::string &filename);

	void write(const std::string &data) override;
};

//File implementation of a LogAdapter, write string of stream to file
class FileLogAdapter : public LogAdapter {
public: 
	FileLogAdapter(const std::string& filename);

	void write(const std::string& data) override;
};

//TransportProtocolAdapter uses an TransportProtocal implementation to send the data
class TransportProtocolAdapter : public LogAdapter {
public: 
	TransportProtocolAdapter(const TransportProtocal &protocol);

	void write(const std::string& data) override;
};









#endif _LOGGERS_HPP 

