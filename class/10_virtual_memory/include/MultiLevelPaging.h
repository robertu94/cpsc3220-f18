#pragma once
#include <vector>
#include <map>
#include "VirtualMemory.h"
#include "StatusBits.h"



class MultiLevelPaging: public VirtualMemory
{
	public:
	MultiLevelPaging(VirtualMemoryOptions options): VirtualMemory(options), page_table(load_page_table_file(options.page_table_file)) {}
	std::uint64_t to_physical(std::uint64_t ptr) override;

	struct PageTableEntry {
		StatusBits status;

		std::uint64_t base_address;
	};
	private:
	static std::map<int,std::vector<PageTableEntry>> load_page_table_file(const char* file_name);
	std::map<int,std::vector<PageTableEntry>> page_table;
};


