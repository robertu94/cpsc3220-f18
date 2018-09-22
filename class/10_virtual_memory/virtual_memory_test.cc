#include <iostream>
#include <iomanip>
#include <vector>

#include "CommandLineOptions.h"

int main(int argc, char *argv[])
{
	auto cl_options = ParseOptions(argc,argv);
	auto num_digits = (cl_options.vm_options.physical_bits / 4) + 2;

	try{
	std::cout << std::showbase << std::hex << std::setw(num_digits) << std::uppercase << std::setfill('0') << std::internal <<
		cl_options.vmem->to_physical(cl_options.address) << std::endl;
	} catch(std::runtime_error& ex) {
		std::cerr << ex.what() << std::endl;
		
	}

	return 0;
}
