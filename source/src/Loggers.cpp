// @file <Loggers.cpp>
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
#include "../include/Loggers.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <pthread.h>
#include <time.h>
#include <BoxMap.hpp>
using namespace std;
void LogAdapter::write(const std::string& data) {}

void ConsoleLogAdapter::write(const std::string &data) {
	//write the string to the console
	std::cout << data << std::endl;
}


FileLogAdapter::FileLogAdapter(const std::string &filename) :
	filename(filename)
{
	fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
	
}

void FileLogAdapter::write(const std::string& data) {
	//write the string to the file
	fs << data << std::endl;
}

Logger::Logger(LogAdapter& logAdapter):
	logAdapter(logAdapter)
{}

DebugLogger::DebugLogger(LogAdapter& logAdapter):
	Logger(logAdapter)
{}

//to change log_type to string
inline const char* DebugLogger::ToString(LOG_TYPE t) {
	switch (t) {
		case LOG_TYPE::VERBOSE: return "VERBOSE";
		case LOG_TYPE::DEBUG:	return "DEBUG";
		case LOG_TYPE::INFO: return "INFO";
		case LOG_TYPE::WARNING: return "WARNING";
		case LOG_TYPE::ERROR: return "ERROR";
	}
}

//log function to say what kind of log_type it is and the string you want to print
void DebugLogger::log(const LOG_TYPE &type, const std::string& massage) {

	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
	std::time_t tt;
	//change time type to be able to change it to a string
	tt = std::chrono::system_clock::to_time_t ( today );
	//time to string
	string time = ctime(&tt);
	//remove the endline character from the time string
	time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());
	//let the logadapter write the whole string
	logAdapter.write("[" + time + "] " + "[" + ToString(type) + "] " + ": " + massage);
}

TelemetryLogger::TelemetryLogger(LogAdapter& logAdapter, const std::string r, const std::string m):
	r(r),
	m(m),
	Logger(logAdapter)
{}


//not functional yet
void* TelemetryLogger::Log(void*) {
	
	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();

	std::time_t tt;	
	tt = std::chrono::system_clock::to_time_t(today);
	string time = ctime(&tt);
	time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());
	logAdapter.write("[" + time + "]" + "Robotstatus: " + r + "Map: " + m);

	
	//map
	string mapFileName = time + " map.log";
	fs.open(mapFileName, std::fstream::in | std::fstream::out | std::fstream::app);
	//r2d2::BoxMap bm{};
    //bm.save(mapFileName);
	fs.close();
	
	
	//////everything under here, doesn't function yet, the architect is looking into it//////
	
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	
	/*
	int milisec = 1000; // length of time to sleep, in miliseconds
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = milisec * 1000000L;
	nanosleep(&req, (struct timespec *)NULL);
	*/
}

TelemetryLoggerTask::TelemetryLoggerTask(TelemetryLogger&){
	//std::thread task(&TelemetryLogger::Log);
	//pthread_t t1;
	//pthread_create(&t1, NULL, &TelemetryLogger::Log, nullptr);
}