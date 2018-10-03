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
  unsigned int duration;
  int seed;
  std::set<SwapAlg> algs;
};

void usage();

Options
parse_args(int argc, char* argv[]);

} // namespace CommandLine
