#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

//shared resources for the philosophers
const int num_philosophers = 5;
std::mutex io_mutex;
std::array<std::mutex, num_philosophers> dining_utensils;

//configure c++ random numbers
std::random_device dev;
std::mt19937 gen(dev());
std::uniform_int_distribution<int> dist(0, 2);

std::mutex&
get_left_hand(int philosopher_id)
{
  return dining_utensils.at(philosopher_id % num_philosophers);
}

std::mutex&
get_right_hand(int philosopher_id)
{
  return dining_utensils.at((philosopher_id + 1) % num_philosophers);
}

void dine(int philosopher_id)
{
	  auto start = std::chrono::system_clock::now();
		std::lock_guard<std::mutex> left_hand(get_left_hand(philosopher_id));
		std::lock_guard<std::mutex> right_hand(get_right_hand(philosopher_id));
	  auto end = std::chrono::system_clock::now();

		auto wait_time = std::chrono::duration_cast<std::chrono::seconds>(end-start);

		{
			std::lock_guard<std::mutex> io_lock(io_mutex);
			std::cout << "Philosopher " << philosopher_id << " dining after waiting " << wait_time.count()  << " seconds" <<  std::endl;
		}

		std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));

}

void think(int philosopher_id )
{
    {
      std::lock_guard<std::mutex> io_lock(io_mutex);
      std::cout << "Philosopher " << philosopher_id << " thinking" << std::endl;
    }
}


void
philosopher(int id)
{
  while (true) {
		dine(id);
		think(id);
	}

}

int
main(int argc, char* argv[])
{
  std::array<std::thread, num_philosophers> philosophers;
  for (int i = 0; i < num_philosophers; ++i) {
    philosophers[i] = std::thread(philosopher, i);
  }

  std::for_each(std::begin(philosophers), std::end(philosophers),
                [](auto& philosopher) { philosopher.join(); });
  return 0;
}
