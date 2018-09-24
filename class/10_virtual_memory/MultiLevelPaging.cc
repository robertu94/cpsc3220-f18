#include "MultiLevelPaging.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <string>

std::uint64_t MultiLevelPaging::to_physical(std::uint64_t ptr)
{
	uint64_t level_1 = getBits(ptr, options.virtual_bits, options.virtual_bits - options.page_bits);
	uint64_t level_2 = getBits(ptr, options.virtual_bits - options.page_bits, options.virtual_bits - options.page_bits - options.page2_bits);
	uint64_t offset = getBits(ptr, std::log2(options.page2_size), 0);

	auto& page = page_table.at(level_1).at(level_2);
	if(offset > options.page_size) throw std::runtime_error("invalid address");

	return page.base_address | offset;
}
std::map<int,std::vector<MultiLevelPaging::PageTableEntry>> MultiLevelPaging::load_page_table_file(const char* file_name)
{
	std::map<int,std::vector<MultiLevelPaging::PageTableEntry>> entries;
	std::ifstream infile(file_name);

	for(std::string line; std::getline(infile, line); )
	{
		int table;
		PageTableEntry pte;

		std::stringstream ss{line};
		ss >> table >> std::hex >> pte.base_address >> pte.status;
		
		entries[table].emplace_back(std::move(pte));
	}

	return entries;
}



