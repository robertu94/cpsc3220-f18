#include "StatusBits.h"

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
