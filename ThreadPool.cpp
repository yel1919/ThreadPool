#include "ThreadPool.h"

using namespace yel;

//std::queue<Task> ThreadPool::taskQueue{};

ThreadPool::ThreadPool(const int num_threads)
	:
	quite(false),
	taskQueue()
{
	threads.reserve(num_threads);
	for (int i = 0; i < num_threads; ++i) {
		threads.emplace_back(&ThreadPool::run, this);
	}
}

ThreadPool::~ThreadPool() {
	quite = true;
	for (int i = 0; i < threads.size(); ++i) {
		threads[i].join();
	}
}

void ThreadPool::start(Task& task) {
	taskQueue.push(&task);
}

void ThreadPool::run() {
	while (!quite) {
		std::unique_lock<std::mutex> lock(tq_mtx);
		tq_cv.wait(lock, [this]()->bool { return !taskQueue.empty() || quite; }); //wait add task in queue

		if (!taskQueue.empty() && !quite) {
			Task* task = taskQueue.front();
			taskQueue.pop();
			lock.unlock();

			task->status_ = TaskStatus::Running;
			task->action();
			task->status_ = TaskStatus::Completed;
		}

		std::cout << std::this_thread::get_id() << std::endl;
	}
	std::cout << "end thread: " << std::this_thread::get_id() << std::endl;
}