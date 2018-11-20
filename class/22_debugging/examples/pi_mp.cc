#include <iostream>

constexpr int steps = 1024*1000;

int main(int argc, char *argv[])
{
	
	double step = 1.0/steps;
	double sum =0.0;

#pragma omp parallel for simd reduction(+:sum)
	for (int i = 1; i < steps; ++i) {
		double x = (i - 0.5) * step;
		sum += (4.0 / (1.0 + x * x));
	}

	double pi = step * sum;
	std::cout << pi << std::endl;

	return 0;
}
