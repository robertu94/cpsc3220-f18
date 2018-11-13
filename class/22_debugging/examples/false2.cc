#include <algorithm>
#include <memory>
#include <random>
#include <vector>
#include <chrono>
#include <iostream>

#include "sizes.h"

using namespace std::chrono;

int
main(int argc, char* argv[])
{
  std::seed_seq seq;
  std::default_random_engine gen{ seq };
  std::uniform_real_distribution<double> dist{};
  auto rand = [&] { return dist(gen); };

  std::vector<double> A;
  A.reserve(size);
  std::generate_n(std::back_inserter(A), size, rand);

	auto begin = high_resolution_clock::now();
#pragma omp parallel for
  for (int i = 0; i < size; ++i) {
    A[i] += 1.0;
  }
	auto end = high_resolution_clock::now();

	std::cout << duration_cast<milliseconds>(end-begin).count() << std::endl;

  return 0;
}

