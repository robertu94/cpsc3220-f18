#include "Commandline.h"

#include <iostream>
#include <string>
#include <map>
#include <unistd.h>



namespace CommandLine {

void
usage()
{
  std::cerr << "./Swap" << std::endl;
}
using namespace std::string_literals;

std::map<std::string, SwapAlg> algs{
  { "opt"s, SwapAlg::OPT },
  { "lru"s, SwapAlg::LRU },
  { "fifo"s, SwapAlg::FIFO },
};

SwapAlg
SwapAlgfromString(std::string name)
{
  auto it = algs.lower_bound(name);
  if (it != algs.end()) {
    return it->second;
  }
  throw std::out_of_range(name);
}



Options
parse_args(int argc, char* argv[])
{
  Options options;
  int opt;

  while ((opt = getopt(argc, argv, "r:s:t:m:i:")) != -1) {
    switch (opt) {
      case 'i':
        options.seed = std::atoi(optarg);
        break;
      case 'm':
        options.memory_sections = std::stoul(optarg);
        break;
      case 'r':
        options.num_requests = std::stoul(optarg);
        break;
      case 's':
        options.memory_size = std::stoul(optarg);
        break;
      case 't':
        options.duration = std::stoul(optarg);
        break;
      default:
        usage();
        exit(EXIT_FAILURE);
    }
  }

  for (; optind < argc; ++optind) {
    options.algs.insert(SwapAlgfromString(argv[optind]));
  }

  if (options.algs.empty()) {
    std::transform(std::begin(algs), std::end(algs),
                   std::inserter(options.algs, std::end(options.algs)),
                   [](auto const& alg) { return alg.second; });
  }

  return options;
}

}
