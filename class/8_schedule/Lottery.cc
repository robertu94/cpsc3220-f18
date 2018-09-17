#include "Lottery.h"
#include <queue>
#include <random>
#include "pusher.hpp"


std::vector<TaskEvent>
LotteryScheduler::schedule(std::vector<Task> const& tasks) const
{
	std::seed_seq seed;
	std::default_random_engine gen(seed);

  size_t current_time = 0;
  std::vector<TaskEvent> events;
  events.reserve(tasks.size());

  std::vector<Task> active;
  std::vector<Task> pending = tasks;

  while (!active.empty() || !pending.empty()) {
    auto now_active = [current_time](auto& task) {
      return task.arrival_time <= current_time;
    };
    // move tasks that are now active to the active queue from the pending queue
    std::copy_if(std::begin(pending), std::end(pending),
                 std::back_inserter(active), now_active);
    pending.erase(
      std::remove_if(std::begin(pending), std::end(pending), now_active),
			std::end(pending)
			);

		if(!active.empty())
		{
			//get a random element and move it the back
			std::uniform_int_distribution<size_t> dist(0, active.size()-1);
			auto idx = dist(gen);
			std::swap(active.at(idx), active.back());
			Task const& current = active.back();

			events.emplace_back(current.id, current.duration, current_time);
			current_time += current.duration;

			active.pop_back();
		} else {
			current_time += 1;
		}

  }

  return events;
}

const char * LotteryScheduler::name() const {
	return "Lottery";
}

