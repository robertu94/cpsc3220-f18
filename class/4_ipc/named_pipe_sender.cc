#include <iostream>
#include <fstream>
#include <string>

const char* FIFO_FILE ="MYFIFO";
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cerr << "USAGE: files_sender [string]";
		exit(1);
	}

	std::ofstream fifo(FIFO_FILE);
	if(fifo)
	{
		std::string line;
		fifo << argv[1];
	} else {
		std::cerr << "fifo does not exist" << std::endl;
	}
	return 0;
}
