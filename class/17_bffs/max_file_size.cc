#include <cmath>
#include <iostream>
struct Config {
	size_t num_direct = 12;
	size_t num_indirect = 1;
	size_t num_double_indirect = 1;
	size_t num_triple_direct = 1;
	size_t num_inodes = 1;
	size_t block_size = 4096;
	size_t pointer_size = 8;
	size_t compute_max_file_size() const {
		return by_direct_pointers() +
			num_indirect * by_indirect(1)+
			num_double_indirect * by_indirect(2)+
			num_triple_direct * by_indirect(3);
	}
	size_t by_direct_pointers() const {
		return num_direct * block_size;
	}
	size_t by_indirect(int level) const {
		return block_size * std::pow((block_size/pointer_size),level);
	}
};


int main(int argc, char *argv[])
{
	Config config;
	std::cout << config.compute_max_file_size() << std::endl;
	return 0;
}
