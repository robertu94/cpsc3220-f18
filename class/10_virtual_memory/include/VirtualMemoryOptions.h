#pragma once
#include <cstdint>

struct VirtualMemoryOptions {
	uint64_t physical_bits = 16;
	uint64_t offset_bits = 10;
	uint64_t virtual_bits = 12;
	uint64_t page_size = 1024;
	uint64_t page_bits = 2;
	const char* segment_file = nullptr;
	const char* page_table_file = nullptr;
};


