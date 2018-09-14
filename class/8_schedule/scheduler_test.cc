#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <random>
#include <stdexcept>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include <memory>
#include <sstream>

#include "getopt.h"

#include "FIFO.h"
#include "RR.h"
#include "SJF.h"
#include "STCF.h"


std::vector<std::string> split(std::string const& text, const char delim)
{
	std::vector<std::string> splits;
	std::istringstream ss(text);
	std::string item;
	while(std::getline(ss, item, delim)) {
			splits.emplace_back(item);
	}
	return splits;
}

std::vector<Task>
make_tasks(const int num_tasks)
{
  std::vector<Task> tasks(num_tasks);
  std::seed_seq seed;
  std::mt19937 gen(seed);
  std::uniform_int_distribution<int> duration_dist(1, 10);
  std::poisson_distribution<int> arrival_dist(5);

  unsigned int id = 0;
  std::generate(std::begin(tasks), std::end(tasks),
                [&id, &gen, &duration_dist, &arrival_dist]() {
                  Task task;
                  task.duration = duration_dist(gen);
                  task.id = id++;
                  task.arrival_time = arrival_dist(gen);
                  task.deadline = std::numeric_limits<std::size_t>::max();
                  return task;
                });

  return tasks;
}

std::vector<std::unique_ptr<Scheduler>>
make_schedulers(int quanta, std::set<std::string> const& tests)
{
  std::vector<std::unique_ptr<Scheduler>> schedulers;
	if(tests.empty())
	{
		schedulers.emplace_back(std::make_unique<FIFOScheduler>());
		schedulers.emplace_back(std::make_unique<SJFScheduler>());
		schedulers.emplace_back(std::make_unique<STCFScheduler>(quanta));
		schedulers.emplace_back(std::make_unique<RRScheduler>(quanta));
	} else {
		for(auto const& test: tests)
		{
			using namespace std::string_literals;
		if(test == "FIFO")
			schedulers.emplace_back(std::make_unique<FIFOScheduler>());
		else if(test == "SJF")
			schedulers.emplace_back(std::make_unique<SJFScheduler>());
		else if(test == "STCF")
			schedulers.emplace_back(std::make_unique<STCFScheduler>(quanta));
		else if(test == "RR")
			schedulers.emplace_back(std::make_unique<RRScheduler>(quanta));
			else
			throw std::runtime_error("the requested scheduler does not exist "s + test);
		}
	}
  return schedulers;
}

void
output_service_and_waiting_times(std::vector<Task> const& tasks,
                                 std::vector<TaskEvent> const& events)
{
  std::map<size_t, size_t> id_to_service_time;
  std::map<size_t, size_t> id_to_response_time;
  std::map<size_t, size_t> id_to_waiting_time;
  std::map<size_t, size_t> id_to_runtime;
  std::map<size_t, size_t> id_to_arrival_time;
  std::map<size_t, size_t> id_to_completion_time;
  std::map<size_t, size_t> id_to_deadline;
	std::map<size_t, size_t> id_to_last_ran;

  for (auto const& task : tasks) {
    id_to_arrival_time[task.id] = task.arrival_time;
    id_to_deadline[task.id] = task.deadline;
  }

  for (auto const& event : events) {
    // only inserts if a new element
    id_to_response_time.emplace(
      event.task_id, event.current_time - id_to_arrival_time[event.task_id]);

		if(id_to_waiting_time.find(event.task_id) != id_to_waiting_time.end())
		{
			id_to_waiting_time[event.task_id] = event.current_time  - id_to_arrival_time[event.task_id];
		} else {
			id_to_waiting_time[event.task_id] += event.current_time - id_to_last_ran[event.task_id];
		}

    // default initializes to 0, add run_time for each task
    id_to_runtime[event.task_id] += event.ran_for;
		id_to_last_ran[event.task_id] = event.ran_for + event.current_time;
  }

  for (auto const& task : tasks) {
    id_to_service_time[task.id] = id_to_last_ran[task.id] - id_to_waiting_time[task.id];
  }

  const int field_width = 12;
  std::cout << std::setw(field_width) << "id" 
		<< std::setw(field_width) << "waiting" 
		<< std::setw(field_width) << "response" 
		<< std::setw(field_width) << "service"
		<< std::setw(field_width) << "run" 
		<< std::setw(field_width) << "ontime" 
		<< std::endl;
	size_t total_waiting_time = 0;
	size_t total_response_time = 0;
	size_t total_service_time = 0;
	size_t total_runtime = 0;
	bool all_met_deadline = true;
  for (auto& task : id_to_service_time) {
    auto& id = task.first;
    auto& service_time = task.second;
    auto waiting_time = id_to_waiting_time[id];
		auto response_time = id_to_response_time[id];
    auto runtime = id_to_runtime[id];
    bool met_deadline = id_to_last_ran[id] < id_to_deadline[id];

		std::cout << std::setw(field_width) << id 
			<< std::setw(field_width) << waiting_time
			<< std::setw(field_width) << response_time
			<< std::setw(field_width) << service_time
			<< std::setw(field_width) << runtime
			<< std::setw(field_width) << std::boolalpha << met_deadline << std::endl;

		total_runtime += runtime;
		total_service_time += service_time;
		total_waiting_time += waiting_time;
		total_response_time += response_time;
		all_met_deadline &= met_deadline;
  }
	std::cout << std::setw(field_width) << "total"
		<< std::setw(field_width) << total_waiting_time
		<< std::setw(field_width) << total_response_time
		<< std::setw(field_width) << total_service_time
		<< std::setw(field_width) << total_runtime
		<< std::setw(field_width) << std::boolalpha << all_met_deadline
		<< std::endl;

  std::cout << "tasks ordering" << std::endl;
  std::transform(std::begin(events), std::end(events),
                 std::ostream_iterator<size_t>(std::cout, " "),
                 [](auto const& event) { return event.task_id; });
}

void
output_task_summary(std::vector<Task> const& tasks)
{
  auto ordered = tasks;
  auto sort_by_arrivals = [](auto const& left, auto const& right) {
    return left.arrival_time < right.arrival_time;
  };

  std::stable_sort(std::begin(ordered), std::end(ordered), sort_by_arrivals);
  std::cout << std::setfill('=') << std::left << "TASKS" << std::setfill(' ')
            << std::right << std::endl;
  output_task_summary_header(std::cout);
  for (auto const& task : ordered) {
    std::cout << task << std::endl;
  }
}

void usage() {
	std::cerr << "./scheduler_test [-n NUM_TASKS] [-q QUANTA]"  << std::endl;
}

int
main(int argc, char* argv[])
{
  int opt;
	int quanta = 3;
	int num_tasks = 5;
	std::set<std::string> tests;
  while((opt = getopt(argc, argv, "n:q:s:")) != -1)
  {
		switch(opt)
		{
			case 'q':
				quanta = atoi(optarg);
				break;
			case 'n':
				num_tasks = atoi(optarg);
				break;
			case 's':
				{
					auto test_names = split(optarg,',');
					std::for_each(std::begin(test_names), std::end(test_names),
							[&tests](std::string const& test) {tests.emplace(test);});
				}
				break;
			default: usage(); exit(EXIT_FAILURE); 
		} 
	}

  const auto tasks = make_tasks(num_tasks);
  auto schedulers = make_schedulers(quanta, tests);

  output_task_summary(tasks);
  for (auto const& scheduler : schedulers) {
    auto events = scheduler->schedule(tasks);
    std::cout << std::left << std::setfill('=') << std::setw(80)
              << scheduler->name() << std::setfill(' ') << std::right
              << std::endl;
    output_service_and_waiting_times(tasks, events);
    std::cout << std::endl;
  }

  return 0;
}
