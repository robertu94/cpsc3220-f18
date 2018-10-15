#include <set>

namespace CommandLine {

enum class SwapAlg
{
  OPT,
  LRU,
  FIFO
};


struct Options
{
  unsigned int num_requests = 10;
  unsigned int memory_sections = 8;
  unsigned int memory_size = 3;
  double duration = 10.0;
  int seed = 0;
	bool quiet = false;
  std::set<SwapAlg> algs;
};

void usage();

Options
parse_args(int argc, char* argv[]);

} // namespace CommandLine
