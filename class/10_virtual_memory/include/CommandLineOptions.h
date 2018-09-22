#pragma once
#include <memory>
#include "VirtualMemory.h"



struct CommandLineOptions {
	size_t address = 0;
	VirtualMemoryOptions vm_options;
	std::unique_ptr<VirtualMemory> vmem;
};

CommandLineOptions ParseOptions(int argc, char* argv[]);
