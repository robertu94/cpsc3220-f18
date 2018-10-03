#include "OPT.h"

#include <algorithm>

bool
OPT::OPTState::in_memory(unsigned int location) const 
{
  return memory.find(location) != std::end(memory);
}

unsigned int
OPT::OPTState::in_use() const 
{
  return memory.size();
}

unsigned int
OPT::OPTState::evict(std::vector<Request>::iterator request,
                     std::vector<Request>::iterator end,
                     unsigned int memory_size) 
{
  unsigned int victim;
  std::set<unsigned int> location_to_next_used;

  for (auto it = request; it != end; ++it) {
    if (in_memory(it->location)) {
      location_to_next_used.emplace(it->location);
      if (in_use() >= memory_size) {
				memory.erase(it->location);
        return it->location;
      }
    }
  }

  // if we finish the loop, at least one of the memory locations are not
  // referenced again use one of these

  std::vector<unsigned int> not_referenced;
  std::set_difference(
    std::begin(memory), std::end(memory), std::begin(location_to_next_used),
    std::end(location_to_next_used), std::back_inserter(not_referenced));
	victim =  not_referenced.front();
  return victim;
}

void OPT::OPTState::page_in(unsigned int location)
{
	memory.emplace(location);
}


const char* OPT::name() const { return "OPT"; }

std::unique_ptr<SwapScheduler::State>
OPT::make_state() const
{
  return std::make_unique<OPTState>();
}

