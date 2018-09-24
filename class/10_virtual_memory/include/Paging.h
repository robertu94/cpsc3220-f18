#pragma once
#include <vector>
#include "VirtualMemory.h"
#include "StatusBits.h"



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

