#include "Segmentation.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

std::uint64_t Segmentation::to_physical(std::uint64_t ptr)
{
	uint64_t segment_id = getBits(ptr, options.virtual_bits, options.offset_bits);
	uint64_t offset = getBits(ptr, options.offset_bits, 0);

	auto& segment = segments.at(segment_id);
	if(offset > segment.size) throw std::runtime_error("invalid address");

	return segment.base_address | offset;
}

std::vector<Segmentation::Segment> Segmentation::load_segment_file(const char* file_name)
{
  std::vector<Segmentation::Segment> segments;
	std::ifstream infile(file_name);

	for(std::string line; std::getline(infile, line); )
	{
		int id;
		Segment segment;
		std::stringstream ss{line};
		ss >> std::hex >> id >> segment.base_address >> segment.size;
		segments.emplace_back(std::move(segment));
	}

	return segments;
}

