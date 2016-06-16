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
#include <thread>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include <pthread.h>
#include <time.h>

#include <BoxMap.hpp>
#include <SharedObject.hpp>
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
void DebugLogger::log(const LOG_TYPE &type, const std::string& message) {

	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
	std::time_t tt;
	//change time type to be able to change it to a string
	tt = std::chrono::system_clock::to_time_t ( today );
	//time to string
	string time = ctime(&tt);
	//remove the endline character from the time string
	time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());
	//let the logadapter write the whole string
	logAdapter.write("[" + time + "] " + "[" + ToString(type) + "] " + ": " + message);
}

TelemetryLogger::TelemetryLogger(LogAdapter& logAdapter, SharedObject<r2d2::RobotStatus>& robot, SharedObject<r2d2::SaveLoadMap>& map):
	robot(robot),
	map(map),
	Logger(logAdapter),
	running(false)
{}




//not functional yet

void TelemetryLogger::start(){
	running = true;
	pthread_create(&threadId, NULL, TelemetryLogger::RUN, static_cast<void*>(this));
	pthread_detach(threadId);
}

void TelemetryLogger::stop(){
	running = false;
	pthread_kill(threadId, 0);
}

bool TelemetryLogger::isRunning(){
	return running;	
}

void* TelemetryLogger::RUN(void* p)
	{
		TelemetryLogger* context = static_cast<TelemetryLogger*>(p);
		while(context->isRunning()) {
			context->Log();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		return NULL;
	}

void TelemetryLogger::Log() {
	
	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();

	std::time_t tt;	
	tt = std::chrono::system_clock::to_time_t(today);
	string time = ctime(&tt);
	time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());
	

	
	//map
	string mapFileName = time + " map.log";
	fs.open(mapFileName, std::fstream::in | std::fstream::out | std::fstream::app);
	SharedObject<r2d2::SaveLoadMap>::Accessor acc(map);
	acc.access().save(mapFileName);
	fs.close();
	//robotstatus doesnt compile yet
	//robotstatus
	/*SharedObject<r2d2::RobotStatus>::Accessor acd(robot);
	SharedObject<r2d2::Speed>::Accessor speed (acd.access().get_current_speed());
	LockingSharedObject<CoordinateAttitude>::Accessor coordinate (acd.access().get_current_coordinate_attitude());

	r2d2::Speed spee = speed.access();
	CoordinateAttitude coor = coordinate.access();
	//double speedo = spee/(1 * r2d2::Speed);
	std::stringstream ss;
	ss << "[" << time << "]" << "Robotstatus: speed: " << spee << "coordinate: " << CoordinateAttitude.get_coordinate().get_X();
	logAdapter.write(ss.str());*/
	
}















