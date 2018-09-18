#include "FIFO.h"
#include <algorithm>
#include <iterator>

std::vector<TaskEvent> FIFOScheduler::schedule(
		std::vector<Task> const& tasks)  const
{
	std::vector<TaskEvent> events;
	events.reserve(tasks.size());
	auto order = tasks;

	std::stable_sort(std::begin(order), std::end(order), [](auto const& left, auto const& right) { return left.arrival_time < right.arrival_time; });

	size_t current_time = 0;
	for(auto& task: order) {
		if(current_time < task.arrival_time) {
			//if the next task has not arrived yet, wait for it.
			current_time = task.arrival_time;
		}
		events.emplace_back(task.id, task.duration, current_time);
		current_time+= task.duration;
	}

	return events;
}

const char* FIFOScheduler::name() const {
	return "FIFO";
}

