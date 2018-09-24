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

std::istream& operator>>(std::istream& in,StatusBits& bits)
{
	std::string status;
	in >> status;
	bits.bits = std::move(std::bitset<7>(status));
	return in;
}

StatusBits::StatusBits()=default;
StatusBits::StatusBits(int bits): bits(bits) {}
bool StatusBits::readable() const { return bits.test(0); }
bool StatusBits::writable() const { return bits.test(1); } 
bool StatusBits::executable() const { return bits.test(2); } 
bool StatusBits::valid() const { return bits.test(3); } 
bool StatusBits::dirty() const { return bits.test(4); } 
bool StatusBits::referenced() const { return bits.test(5); } 
bool StatusBits::present() const { return bits.test(6); } 

