#include <thread>
#include <mutex>
#include <iostream>

const long int BIG = 100000000L;
unsigned long counter = 0;
std::mutex lock;

void count_to_big(int id)
{
	std::lock_guard<std::mutex> guard(lock);
	std::cout << id << std::endl;
	for (long int i = 0; i < BIG; ++i) {
		counter++;
	}
}

int main(int argc, char *argv[])
{
	std::thread t1(count_to_big, 0);
	std::thread t2(count_to_big, 1);

	t1.join();
	t2.join();
	std::cout << counter << std::endl;
	return 0;
}
