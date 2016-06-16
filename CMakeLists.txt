
cmake_minimum_required(VERSION 2.8.9)
project( logging_and_telemetry )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -Wall") 
SET(GCC_COVERAGE_LINK_FLAGS    -lpthread)
find_package (Threads)


file(GLOB SOURCES "source/src/*.cpp" 
		"source/include/*.hpp"
		"../map/source/src/MapInterface.cpp" 
		"../sensorInterfaces/source/include/CoordinateAttitude.hpp" 
		"../sensorInterfaces/source/src/CoordinateAttitude.cpp" 		
		"../pilot/source/include/RobotStatus.hpp" 
		"../pilot/source/src/RobotStatus.cpp" 
		"../map/source/include/MapInterface.hpp"
		"../map/source/include/ArrayBoxMap.hpp"
		"../map/source/src/ArrayBoxMap.cpp"
		"../map/source/include/BoxMap.hpp"
		"../map/source/src/BoxMap.cpp"
		"../sharedobjects/source/include/SharedObject.cpp"
		"../adt/source/include/ADT_Base.hpp"
		"../adt/source/src/Length.cpp"
		"../adt/source/src/Box.cpp"
		"../adt/source/src/Coordinate.cpp"
		"../adt/source/src/Translation.cpp")
file(GLOB SOURCES_GTEST "source/src/*.cpp" "source/include/*.hpp" "test/*.cpp" "test/*.hpp"
"../map/source/src/MapInterface.cpp" 
		"../pilot/source/src/RobotStatus.cpp" 
		"../map/source/include/MapInterface.hpp"
		"../map/source/include/MapInterface.hpp"
		"../map/source/include/ArrayBoxMap.hpp"
		"../map/source/src/ArrayBoxMap.cpp"
		"../map/source/include/BoxMap.hpp"
		"../map/source/src/BoxMap.cpp"
		"../sharedobjects/source/include/SharedObject.cpp"
		"../adt/source/include/ADT_Base.hpp"
		"../adt/source/src/Length.cpp"
		"../adt/source/src/Box.cpp"
		"../adt/source/src/Coordinate.cpp"
		"../adt/source/src/Translation.cpp")
list(REMOVE_ITEM SOURCES_GTEST ${CMAKE_CURRENT_SOURCE_DIR}/source/src/Main.cpp)

include_directories(
	../sensorInterfaces/source/include
	../pilot/source/include
	../map/source/include
   	../adt/source/include
	../sharedobjects/source/include
  	../deps/gtest-1.7.0/include
  	../deps/gtest-1.7.0)



link_directories(../deps/gtest-1.7.0/src	../map/source/src ../adt/source/src)
ADD_LIBRARY(gtest ../deps/gtest-1.7.0/src/gtest-all.cc)
ADD_LIBRARY(gtest_main ../deps/gtest-1.7.0/src/gtest_main.cc)
add_executable(logging_and_telemetry ${SOURCES})
add_executable(logging_and_telemetry_test ${GTEST} ${SOURCES_GTEST})
target_link_libraries(logging_and_telemetry_test gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})