#include "../include/Loggers.hpp"

#include <string>

int main() {
	FileLogAdapter fla("test.txt");
	ConsoleLogAdapter cla;
	cla.write("this is a test for the console");
	fla.write("Hello World! Test Test");

	DebugLogger dl(fla);
	dl.log(DebugLogger::LOG_TYPE::INFO, "dit is een mooie test");

	while(true);
}