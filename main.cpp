#include "ThreadPool.h"

int main(int argc, char** argv) {
	yel::ThreadPool pool(3);

	yel::Task task1(
		[]() {
			std::cout << "do work. task_id = " << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			std::cout << "work complited" << std::endl;
		}
	);

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	return 0;
}