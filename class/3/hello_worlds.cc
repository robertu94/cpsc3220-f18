#include <iostream>
#include <unistd.h>
int main(int argc, char *argv[])
{
	int ret = fork();
	int ret2 = fork();
	std::cout << "I am the process that returned " << ret << " and " << ret2 << std::endl;
	return 0;
}
