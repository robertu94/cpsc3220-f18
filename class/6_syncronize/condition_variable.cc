#include <algorithm>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>


namespace {
struct Task {
	template<class... Args>
		Task(int duration, Args&&... name) : duration(), name(std::forward<Args>(name)...) {}

	unsigned int  duration;
	std::string name;
};

template<class T>
class Queue {
	public:
		Queue(): queue_lock(), queue_cond(), queue() {}

		template<class... Args>
		void emplace(Args&&... args) {
			std::unique_lock<std::mutex> lock(queue_lock);
			queue_cond.notify_one();
			queue.emplace(std::forward<Args>(args)...);
		}

		T pop() {
			std::unique_lock<std::mutex> lock(queue_lock);
			queue_cond.wait(lock, [this]() { return !queue.empty();});

			T elm = std::move(queue.front());
			queue.pop();
			return elm;
		}

	private:
		std::mutex queue_lock;
		std::condition_variable queue_cond;
		std::queue<T> queue;

};

}

Queue<Task> task_queue;
const unsigned int num_readers = 5;
std::mutex io_mutex;

void producer() {
	while(true)
	{
		{
			std::lock_guard<std::mutex> io_lock(io_mutex);
			std::cout << "pushing new tasks" << std::endl;
		}
		task_queue.emplace(1, "task 1");
		task_queue.emplace(2, "task 2");
		task_queue.emplace(3, "task 3");
		task_queue.emplace(2, "task 4");
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

}

void consumer(int id) {
	while(true)
	{
		Task task = task_queue.pop();
		{
			std::lock_guard<std::mutex> io_lock(io_mutex);
			std::cout << "worker " << id << " doing " << task.name << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::seconds(task.duration));
	}
}

int main(int argc, char *argv[])
{
	auto producer_thrd = std::thread(producer);
	std::vector<decltype(std::thread(consumer, num_readers))> readers;
	readers.reserve(num_readers);
	for (int i = 0; i < num_readers; ++i) {
		readers.emplace_back(consumer, i);	
	}


	producer_thrd.join();
	std::for_each(std::begin(readers), std::end(readers), [](auto&& reader) {reader.join();});
	return 0;
}
