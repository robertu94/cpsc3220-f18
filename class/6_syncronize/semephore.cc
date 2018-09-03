#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>

const int num_workers = 8;
std::mutex io_mutex;
std::random_device dev;
std::mt19937 gen(dev());
std::uniform_int_distribution<int> dist(2, 8);

class Semaphore
{
public:
  Semaphore(int count = 0)
    : mtx()
    , cv()
    , count(count)
  {}

  void notify()
  {
    std::unique_lock<std::mutex> lock(mtx);
    ++count;
    cv.notify_one();
  }

  void wait()
  {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return count > 0; });
    --count;
  }

private:
  std::mutex mtx;
  std::condition_variable cv;
  int count;
} sem(6);

class SemaphoreGuard
{
public:
  SemaphoreGuard(Semaphore& sem)
    : sem(sem)
  {
    sem.wait();
  }
  ~SemaphoreGuard() { sem.notify(); }

private:
  Semaphore& sem;
};

void
worker(int id)
{
  while (true) {
    SemaphoreGuard sem_guard(sem);

    {
      std::lock_guard<std::mutex> lock(io_mutex);
      std::cout << "worker " << id << " started" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(dist(gen)));

    {
      std::lock_guard<std::mutex> lock(io_mutex);
      std::cout << "worker " << id << " done" << std::endl;
    }
  }
}

int
main(int argc, char* argv[])
{
  std::array<std::thread, num_workers> threads;
  for (int i = 0; i < num_workers; ++i) {
    threads[i] = std::thread(worker, i);
  }

  std::for_each(std::begin(threads), std::end(threads),
                [](auto& thread) { thread.join(); });
  return 0;
}
