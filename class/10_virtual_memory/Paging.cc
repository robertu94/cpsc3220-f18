#include "Paging.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <string>

std::uint64_t Paging::to_physical(std::uint64_t ptr)
{
	uint64_t page_id = getBits(ptr, options.virtual_bits, options.virtual_bits - options.page_bits);
	uint64_t offset = getBits(ptr, std::log2(options.page_size), 0);

	auto& page = page_table[page_id];
	if(offset > options.page_size) throw std::runtime_error("invalid address");

	return page.base_address | offset;
}
std::vector<Paging::PageTableEntry> Paging::load_page_table_file(const char* file_name)
{
	std::vector<Paging::PageTableEntry> entries;
	std::ifstream infile(file_name);

	for(std::string line; std::getline(infile, line); )
	{
		int table; /*ignored for single level page table*/
		PageTableEntry pte;

		std::stringstream ss{line};
		ss >> table >> std::hex >> pte.base_address >> pte.status;
		
		entries.emplace_back(std::move(pte));
	}

	return entries;
}

