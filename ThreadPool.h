#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

#include "Task.h"

namespace yel {
	class ThreadPool {
	public:
		ThreadPool(const int n);
		ThreadPool(const ThreadPool&) = delete;
		virtual ~ThreadPool();

		ThreadPool& operator=(const ThreadPool&) = delete;
		void start(Task& task);
	protected:
		virtual void run();
	private:
		std::queue<Task*> taskQueue;
		std::mutex tq_mtx;
		std::condition_variable tq_cv;

		
		std::vector<std::thread> threads;
		std::atomic<bool> quite;
	};
}

#endif // !THREADPOOL_H