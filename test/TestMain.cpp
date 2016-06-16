#include "../../deps/gtest-1.7.0/include/gtest/gtest.h"
#include "../source/include/Loggers.hpp"

#include <iostream>
#include <fstream>
#include <string>

#define MAP_TEST_SIZE 100
 r2d2::DefaultBoxMap box(){
	r2d2::DefaultBoxMap bm{};


	for (int y = 0; y < MAP_TEST_SIZE; ++y) {
		for (int x = 0; x < MAP_TEST_SIZE; ++x) {
			r2d2::Coordinate new_pos{
					x * r2d2::Length::METER,
					y * r2d2::Length::METER,
					-1 * r2d2::Length::METER
			};

			r2d2::BoxInfo info{
					rand() % 2 == 0,
					rand() % 2 == 0,
					rand() % 2 == 0};

			bm.set_box_info(
					r2d2::Box{
							new_pos,
							new_pos
							+ r2d2::Translation{
									2 * r2d2::Length::METER,
									2 * r2d2::Length::METER,
									2 * r2d2::Length::METER
							}
					},
					info.get_has_obstacle() || info.get_has_navigatable() ? info : r2d2::BoxInfo{
							(x ^ y) % 2 == 0,
							(x ^ y) % 2 == 1,
							info.get_has_unknown()
					}
			);
		}
	}
	return bm;

}

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
	
	r2d2::DefaultBoxMap bm{box()};
	LockingSharedObject<r2d2::SaveLoadMap> ding(bm);
	
	TelemetryLogger tl(fla, m1, ding);
	
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}