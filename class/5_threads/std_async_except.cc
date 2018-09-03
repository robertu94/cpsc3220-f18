#include <iostream>
#include <future>
#include <stdexcept>

unsigned long int BIG = 1000000L;

int count_may_except(int id) 
{
	if(id>=3) {
		throw std::runtime_error("does not support ids greater or equal to 3");
	}

	int counter = 0;
	for (int i = 0; i < BIG; ++i) {
		counter++;
	}
	return counter;
}
int main(int argc, char *argv[])
{
	int count = 5;
	try{
		for (int i = 0; i < count; ++i) {
			auto future_may_except = std::async(std::launch::async,count_may_except, i);
			std::cout << future_may_except.get()  << std::endl;
		}
	} catch (std::exception const& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
