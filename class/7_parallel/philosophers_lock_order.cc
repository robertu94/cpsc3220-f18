#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

// shared resources for the philosophers
const int num_philosophers = 5;
std::mutex io_mutex;
std::array<std::mutex, num_philosophers> dining_utensils;

// configure c++ random numbers
std::random_device dev;
std::mt19937 gen(dev());
std::uniform_int_distribution<int> dist(0, 2);

int
get_left_hand(int philosopher_id)
{
  return philosopher_id % num_philosophers;
}

int
get_right_hand(int philosopher_id)
{
  return (philosopher_id + 1) % num_philosophers;
}

std::pair<int, int>
get_hands(int philosopher_id)
{
  int left_hand_id = get_left_hand(philosopher_id);
  int right_hand_id = get_right_hand(philosopher_id);
  int lower = std::min(left_hand_id, right_hand_id);
  int higher = std::max(left_hand_id, right_hand_id);
  return std::make_pair(lower, higher);
}

void
dine(int philosopher_id)
{
  auto start = std::chrono::system_clock::now();
  /*
   * There are 4 necessary and sufficient cases for deadlock.  All must be
   * present to cause deadlock:
   *
   * 1. Mutual exclusion -- resources cannot be shared
   * 2. Hold and wait (blocking) semantics -- once a lock in a set is acquired,
   *    the process is blocked until it requires all locks
   * 3. No Preemption -- no thread that can steal locks from other threads
   * 4. Circular Wait -- if there is a cycle in the order the locks are acquired
	 *
   * In this version we ensure an ordering to the locks to prevent circular
   * waiting.
   */
  auto hands = get_hands(philosopher_id);
  std::lock_guard<std::mutex> left_hand(dining_utensils.at(hands.first));
  std::lock_guard<std::mutex> right_hand(dining_utensils.at(hands.second));
  auto end = std::chrono::system_clock::now();

  auto wait_time =
    std::chrono::duration_cast<std::chrono::seconds>(end - start);

  {
    std::lock_guard<std::mutex> io_lock(io_mutex);
    std::cout << "Philosopher " << philosopher_id << " dining after waiting "
              << wait_time.count() << " seconds" << std::endl;
  }

  std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));
}

void
think(int philosopher_id)
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
