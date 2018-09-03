#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <shared_mutex>
#include <thread>

const int num_threads = 5;
unsigned long counter = 0;
std::random_device dev;
std::mt19937 gen(dev());
std::uniform_int_distribution<int> dist(0, 2);

std::shared_timed_mutex reader_writer_mutex;
std::mutex io_mutex;

void
writer_thread_func()
{
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(4));
    {
			//grab the lock for writing
      std::unique_lock<std::shared_timed_mutex> writer_lock(
        reader_writer_mutex);

      {
				//don't hold the io_mutex while sleeping
        std::unique_lock<std::mutex> io_lock(io_mutex);
        std::cout << "writing!" << std::endl;
      }

			//intentional sleep with writer lock
      std::this_thread::sleep_for(std::chrono::seconds(3));
      counter++;

      {
				//don't hold the io_mutex while sleeping
        std::unique_lock<std::mutex> io_lock(io_mutex);
        std::cout << "writing done!" << std::endl;
      }
    } //release the lock from writing
  }
}

void
reader_thread_func(int id)
{
  while (true) {
    {
			//grab the lock for reading
      std::shared_lock<std::shared_timed_mutex> reader_lock(
        reader_writer_mutex);
      std::lock_guard<std::mutex> io_lock(io_mutex);
      std::cout << "thread " << id << " read " << counter << std::endl;
    } //release the lock from reading
    std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));
  }
}

int
main(int argc, char* argv[])
{
  std::array<std::thread, num_threads> readers;
  std::thread writer;

  for (int reader_id = 0; reader_id < num_threads; ++reader_id) {
    readers[reader_id] = std::thread(reader_thread_func, reader_id);
  }
  writer = std::thread(writer_thread_func);

  writer.join();
  std::for_each(std::begin(readers), std::end(readers),
                [](auto& reader) { reader.join(); });
  return 0;
}
