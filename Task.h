#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <functional>
#include <queue>

typedef unsigned long ulong;
typedef ulong task_id;

namespace yel {
    class Task;
    class ThreadPool;

    enum class TaskStatus {
        Created,
        Running,
        Completed
    };

    class Task {
        friend ThreadPool;
    public:
        Task(const std::function<void()>& action);
        Task(const Task& task);
        Task(Task&& task) noexcept;
        virtual ~Task();

        Task& operator=(const Task& task);
        Task& operator=(Task&& task) noexcept;

        const task_id& id() const;
        const TaskStatus& status() const;
    protected:
    private:
        static std::atomic<task_id> last_idx;
        TaskStatus status_;
        task_id id_;
        std::function<void()> action;
    };
}

#endif // !TASK_H