#include "Scheduler.h"
#include <iomanip>
#include <limits>

std::ostream&
operator<<(std::ostream& out, TaskEvent const& te)
{
  return out << std::setw(16) << te.task_id << std::setw(16) << te.ran_for
             << std::setw(16) << te.current_time;
}

void
print_taskevent_summary_headers(std::ostream& out)
{
  out << std::setw(16) << "task_id" << std::setw(16) << "ran_for"
             << std::setw(16) << "current_time" << std::endl;
}

std::ostream&
operator<<(std::ostream& out, Task const& task)
{

  return out << std::setw(16) << task.id << std::setw(16) << task.duration
             << std::setw(16) << task.arrival_time << std::setw(16)
             << (int)((task.deadline == std::numeric_limits<std::size_t>::max())?task.deadline:-1);
};

void
output_task_summary_header(std::ostream& out)
{
  out << std::setw(16) << "id" << std::setw(16) << "duration" << std::setw(16)
      << "arrival_time" << std::setw(16) << "deadline" << std::endl;
}

