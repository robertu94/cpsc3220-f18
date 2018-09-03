#include <future>
#include <iostream>
#include <numeric>
#include <vector>
#include <unistd.h>

const long int BIG = 100000000L;


long int count_to_big(int i)
{
  int counter = 0;
  for (long int i = 0; i < BIG; ++i) {
    counter++;
  }
	std::cout << "done " << i << std::endl;
  return counter;
}

int
main(int argc, char* argv[])
{
	const int count = 10;
  std::vector<decltype(std::async(count_to_big, count))> futures;
	futures.reserve(count);
  for (int i = 0; i < count; ++i) {
     futures.emplace_back(std::async(std::launch::deferred, count_to_big, i));
  }

	std::cout << "sleeping" << std::endl;
	sleep(3);
	std::cout << "done sleeping" << std::endl;

  unsigned long long  counter = std::accumulate(std::begin(futures), std::end(futures), 0ull,
                                [](unsigned long long cumulative_sum, auto&& future) {
                                  return cumulative_sum + future.get();
                                });

  std::cout << counter << std::endl;
  return 0;
}


