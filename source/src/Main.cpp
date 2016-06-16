#include "../include/Loggers.hpp"
#include <DefaultBoxMap.hpp>
#include <string>
#include <thread>
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
int main() {
	FileLogAdapter fla("test.txt");

	DebugLogger dl(fla);
	dl.log(DebugLogger::LOG_TYPE::INFO, "dit is een mooie test");
	r2d2::DefaultBoxMap bm{box()};

	LockingSharedObject<r2d2::SaveLoadMap> ding(bm);
	FileLogAdapter fla1("telemetry.log");
	
	TelemetryLogger tl(fla1, "mooi", ding );
	tl.start();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	tl.stop();
	

}