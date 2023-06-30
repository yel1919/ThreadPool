#include "Task.h"

using namespace yel;

std::atomic<task_id> Task::last_idx = 0;

Task::Task(const std::function<void()>& action) 
	:
	status_(TaskStatus::Created),
	id_(0),
	action(action)
{}

Task::Task(const Task& task) 
	:
	status_(task.status_),
	id_(task.id_),
	action(task.action)
{}

Task::Task(Task&& task) noexcept
	:
	status_(task.status_),
	id_(task.id_)
{
	task.status_ = TaskStatus::Created;
	task.id_ = 0;
	action = std::move(task.action);
}

Task::~Task() {
	id_ = 0;
	action = nullptr;
	last_idx--;
}

Task& Task::operator=(const Task& task) {
	if (this != &task) {
		status_ = task.status_;
		id_ = task.id_;
		action = task.action;
	}
	return *this;
}

Task& Task::operator=(Task&& task) noexcept {
	if (this != &task) {
		action = std::move(task.action);
		status_ = task.status_;
		id_ = task.id_;
		
		task.status_ = TaskStatus::Created;
		task.id_ = 0;
	}
	return *this;
}

const task_id& Task::id() const {
	return id_;
}

const TaskStatus& Task::status() const {
	return status_;
}