#include <iostream>
#include <string>
int main()
{
	std::string name;
	std::cin >> name;
	if(std::cin)
		std::cout << "hello world " << name << std::endl;
	return 0;
}
