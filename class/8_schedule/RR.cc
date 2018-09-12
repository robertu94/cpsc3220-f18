#include "RR.h"
#include <algorithm>
#include <deque>
#include <iterator>

std::vector<TaskEvent>
RRScheduler::schedule(std::vector<Task> const& tasks) const
{
  size_t current_time = 0;
  std::vector<TaskEvent> events;
  std::deque<Task> active;
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
      std::end(pending));



    if (!active.empty()) {
      Task& current = active.front();
			auto run_for =std::min(quanta, current.duration);
      events.emplace_back(current.id, run_for, current_time);
      current_time += run_for;
      current.duration -= run_for;

      if (current.duration <= 0) {
        active.pop_front();
      }

      std::rotate(std::begin(active), std::next(std::begin(active)),
                  std::end(active));
    } else {
      current_time += 1;
    }
  }
  return events;
}

const char*
RRScheduler::name() const
{
  return "RR";
}

