#pragma once
#include <cstddef>
#include <vector>
#include <string>

struct TaskEvent
{
  TaskEvent(std::size_t id, std::size_t ran_for, std::size_t current_time)
    : task_id(id)
    , ran_for(ran_for)
    , current_time(current_time)
  {}
  std::size_t task_id;
  std::size_t ran_for;
  std::size_t current_time;
};
std::ostream& operator<<(std::ostream&, TaskEvent const&);
void output_taskevent_summary_header(std::ostream&);

struct Task {
	std::size_t id;
	std::size_t duration;
	std::size_t deadline; /*not used until class 9 */
	std::size_t arrival_time;
};
std::ostream& operator<<(std::ostream&, Task const&);
void output_task_summary_header(std::ostream&);

class Scheduler
{
public:
  virtual ~Scheduler() = default;
  virtual std::vector<TaskEvent> schedule(std::vector<Task> const& tasks) const = 0;
	virtual const char* name() const = 0;
};
