#pragma once

#include <vector>
#include "VirtualMemory.h"

class Segmentation: public VirtualMemory
{
	public:
	Segmentation(VirtualMemoryOptions options): VirtualMemory(options), segments(load_segment_file(options.segment_file)) {}
	std::uint64_t to_physical(std::uint64_t ptr) override;

	struct Segment {
		std::uint64_t base_address;
		std::uint64_t size;
	};
	private:
	static std::vector<Segment> load_segment_file(const char* file_name);
  std::vector<Segmentation::Segment> segments;
};
