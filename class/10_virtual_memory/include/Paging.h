#pragma once
#include <vector>
#include "VirtualMemory.h"

class Paging: public VirtualMemory
{
	public:
	Paging(VirtualMemoryOptions options): VirtualMemory(options), page_table(load_page_table_file(options.segment_file)) {}
	std::uint64_t to_physical(std::uint64_t ptr) override;

	struct PageTableEntry {
		std::uint64_t base_address;
	};
	private:
	static std::vector<PageTableEntry> load_page_table_file(const char* file_name);
  std::vector<PageTableEntry> page_table;
};

