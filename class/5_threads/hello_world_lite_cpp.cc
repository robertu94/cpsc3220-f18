#include <thread>
#include <mutex>
#include <iostream>

const long int BIG = 100000000L;
unsigned long counter = 0;
std::mutex lock;

void count_to_big()
{
	for (long int i = 0; i < BIG; ++i) {
		std::lock_guard<std::mutex> guard(lock);
		counter++;
	}
}

int main(int argc, char *argv[])
{
	std::thread t1(count_to_big);
	std::thread t2(count_to_big);

	t1.join();
	t2.join();
	std::cout << counter << std::endl;
	return 0;
}
