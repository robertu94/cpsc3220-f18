#pragma once
#include "VirtualMemoryOptions.h"

class VirtualMemory
{
	public:
		VirtualMemory(VirtualMemoryOptions options): options(options) {};
		~VirtualMemory()=default;
		static std::uint64_t getBits(std::uint64_t ptr, std::uint64_t high_bit, std::uint64_t low_bit);
		virtual std::uint64_t to_physical(std::uint64_t ptr) = 0;

	protected:
		VirtualMemoryOptions options;
};
