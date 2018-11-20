#include <future>
#include <iostream>
#include <vector>
#include <numeric>

constexpr int steps = 100000000;
constexpr double step = 1.0/steps;
constexpr int size = 8;
constexpr int width = steps / size;

double kernel(int start, int stop)
{
	double local_sum=0.0;
	for (int i = start; i < stop; ++i) {
		double x = (i - 0.5) * step;
		local_sum += (4.0/(1.0 + x * x));
	}
	return local_sum;
}

int main(int argc, char *argv[])
{
	std::vector<std::future<double>> futures;

	for (int rank = 0; rank < size; ++rank) {
		int start = rank * width;
		int stop  = start + width;
		futures.emplace_back(std::async(std::launch::async, kernel, start, stop));
	}

	double global_sum =0;
	for (auto& future : futures) {
		global_sum += future.get();
	}
	global_sum *= step;

	std::cout << global_sum << std::endl;
	return 0;
}
