#include "VirtualMemory.h"
#include <cassert>
#include <climits>

namespace {
inline constexpr uint64_t make_mask(int bits) {
	uint64_t mask = 0;
	while(bits-- > 0) mask = (mask<<1)+1;
	return mask;
}

}

uint64_t VirtualMemory::getBits(std::uint64_t ptr, std::uint64_t high, std::uint64_t low)
{
		assert(low < high);
		auto low_mask = make_mask(low);
		auto high_mask = make_mask(high);
		auto mask = high_mask & (~low_mask);
		return (ptr & mask) >> low;
}
