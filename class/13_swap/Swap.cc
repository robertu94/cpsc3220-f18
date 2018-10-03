#include <memory>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "SwapScheduler.h"
#include "LRU.h"
#include "OPT.h"
#include "FIFO.h"

std::unique_ptr<SwapScheduler>
make_disk_scheduler(CommandLine::SwapAlg alg, unsigned int memory_size)
{
	using namespace CommandLine;
  std::unique_ptr<SwapScheduler> scheduler;

  switch (alg) {
    case SwapAlg::FIFO:
      scheduler = std::make_unique<FIFO>(memory_size);
      break;
    case SwapAlg::LRU:
      scheduler = std::make_unique<LRU>(memory_size);
      break;
    case SwapAlg::OPT:
      scheduler = std::make_unique<OPT>(memory_size);
      break;
  }

  return scheduler;
}

int
main(int argc, char* argv[])
{
  auto options = CommandLine::parse_args(argc, argv);
  auto requests = generate_requests(options);

  std::cout << "Requests Arrived" << std::endl;
  std::cout << "arrival_time\tlocation" << std::endl;
  std::copy(std::begin(requests), std::end(requests),
            std::ostream_iterator<Request>(std::cout, "\n"));

  for (auto i : options.algs) {
    auto scheduler = make_disk_scheduler(i, options.memory_size);
		auto events = scheduler->schedule(requests);
		std::cout << scheduler->name() << std::endl;
		for(auto const& event: events)
		{
			std::cout << event << std::endl;
		}
  }

  return 0;
}
