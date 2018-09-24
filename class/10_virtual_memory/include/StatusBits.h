#pragma once
#include <bitset>
#include <StatusBits.h>

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


