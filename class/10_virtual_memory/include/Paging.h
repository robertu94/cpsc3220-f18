#pragma once
#include <vector>
#include <bitset>
#include "VirtualMemory.h"

class StatusBits {
	public:
		StatusBits();
		StatusBits(int);

		bool readable() const;
		bool writable() const;
		bool executable() const;
		bool valid() const;
		bool dirty() const;
		bool referenced() const;
		bool present() const;

	private:
		std::bitset<7> bits;
		friend std::istream& operator>>(std::istream&,StatusBits&);
};

std::istream& operator>>(std::istream& in,StatusBits& bits);



class Paging: public VirtualMemory
{
	public:
	Paging(VirtualMemoryOptions options): VirtualMemory(options), page_table(load_page_table_file(options.page_table_file)) {}
	std::uint64_t to_physical(std::uint64_t ptr) override;

	struct PageTableEntry {
		StatusBits status;

		std::uint64_t base_address;
	};
	private:
	static std::vector<PageTableEntry> load_page_table_file(const char* file_name);
  std::vector<PageTableEntry> page_table;
};

