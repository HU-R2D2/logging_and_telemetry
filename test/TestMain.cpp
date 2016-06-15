#include "../../deps/gtest-1.7.0/include/gtest/gtest.h"
#include "../source/include/Loggers.hpp"
#include <iostream>
#include <fstream>
#include <string>

TEST(LoggerTest, FileWriteTest) {
	std::string file = "FileWriteTest.txt";
	std::string message = "Hello World! This is a test";
	FileLogAdapter fla(file);
	fla.write(message);
	std::string output;

	std::ifstream myReadFile;
	myReadFile.open(file);
	if (myReadFile.is_open()) {
		std::string line;
		bool loop = true;
		while (loop) {
			std::getline(myReadFile, line);
			if (line != "") {
				output = line;
			}
			else {
				loop = false;
			}
		}
	}
	myReadFile.close();
	EXPECT_EQ(message, output);
}

TEST(LoggerTest, DebugLoggerTest) {
	std::string file = "DebugLoggerTest.txt";
	std::string message = "Dit is een mooie test";
	FileLogAdapter fla(file);
	DebugLogger dl(fla);
	dl.log(DebugLogger::LOG_TYPE::INFO, message);

	std::ifstream myReadFile;
	std::string output;
	myReadFile.open(file);
	if (myReadFile.is_open()) {
		std::string line;
		bool l = true;
		while (l) {
			std::getline(myReadFile, line);
			if (line != "") {
				output = line;
			}
			else {
				l = false;
			}
		}
	}
	myReadFile.close();

	std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
	std::time_t tt;
	tt = std::chrono::system_clock::to_time_t(today);
	std::string time = ctime(&tt);
	time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());

	std::string test = "[" + time + "] " + "[INFO] : " + message;
		
	EXPECT_EQ(test, output);
}

TEST(LoggerTest, TelemetryLoggerTest) {
	std::string file = "TelemetryLoggerTest.log";
	std::string m1 = "mooi";
	std::string m2 = "cool";
	FileLogAdapter fla(file);
	TelemetryLogger tl(fla, m1, m2);
	TelemetryLoggerTask tlt(tl);
	
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}