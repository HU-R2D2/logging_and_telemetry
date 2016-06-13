// @file <Loggers.hpp>
// @date Created: <07-06-16>
// @version <0.1.0>
//
// @author <Robert Zegers>
//
// @section LICENSE
// License: newBSD
//
// Copyright � 2016, HU University of Applied Sciences Utrecht.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with
// or without modification, are permitted provided
// that the following conditions are met:
// - Redistributions of source code must retain the above
// copyright notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the
// above copyright notice, this list of conditions and the
// following disclaimer in the documentation and/or
// other materials provided with the distribution.
// - Neither the name of the HU University of
// Applied Sciences Utrecht nor the names of its contributors
// may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ++--++
#ifndef _LOGGERS_HPP
#define _LOGGERS_HPP
#include <ctime>
#include <chrono>
#include <algorithm>
#include <string>
#include <fstream>
#include "RobotStatus.hpp"
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

	void log(const LOG_TYPE &type, const std::string& massage); // const std::string& time => const Clock::TimeStamp& time 

private:
	inline const char* ToString(LOG_TYPE t);
};

//Telemetry implementation of a Logger. Gather data and write it to the adapter. 
class TelemetryLogger : Logger {
	TelemetryLogger(const LogAdapter&, const SharedObject<RobotStatus>&, const SharedObject<Map>&);

	void log();
};

#endif