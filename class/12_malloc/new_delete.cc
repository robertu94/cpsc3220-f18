#include <cstdlib>
#include <iostream>
#include <memory>

void* operator new(std::size_t size)
{
	std::cout << "allocating: " << size << std::endl;
	return std::malloc(size);
}

void operator delete(void* ptr) noexcept
{
	std::cout << "freeing" << ptr << std::endl;
	std::free(ptr);
}


int main(int argc, char *argv[])
{
	std::cout << "raw pointer"  << std::endl;
	int* i = new int; 
	delete i;

	std::cout << std::endl	<< "raw pointer array"  << std::endl;
	int* j = new int[4]; 
	delete[] j;

	{
		std::cout << std::endl << "smart pointer"  << std::endl;
		auto k = std::make_unique<int>(4);
	}

	{
		std::cout << std::endl << "smart pointer array"  << std::endl;
		auto l = std::make_unique<int[]>(4);
	}
	
	return 0;
}
