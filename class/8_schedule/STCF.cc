#include "STCF.h"
#include <algorithm>
#include <iterator>

std::vector<TaskEvent>
STCFScheduler::schedule(std::vector<Task> const& tasks) const
{
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
      std::end(pending));

    if (!active.empty()) {

      // sort tasks on shortest job last because removal from the back is fast,
      // removal from the front is slow
      std::sort(std::begin(active), std::end(active),
                [](auto const& left, auto const& right) {
                  return left.duration > right.duration;
                });

      Task& current = active.back();
      auto run_for = std::min(quanta, current.duration);
      events.emplace_back(current.id, run_for, current_time);
      current_time += run_for;
      current.duration -= run_for;

      if (current.duration <= 0) {
        active.pop_back();
      }
    } else {
      current_time += 1;
    }
  }

  return events;
}

const char*
STCFScheduler::name() const
{
  return "STCF";
}
