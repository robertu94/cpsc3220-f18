#include "FIFO.h"

bool
FIFO::FIFOState::in_memory(unsigned int location) const 
{
  return memory.find(location) != memory.end();
}

unsigned int
FIFO::FIFOState::in_use() const 
{
  return memory.size();
}

unsigned int
FIFO::FIFOState::evict(std::vector<Request>::iterator request,
                       std::vector<Request>::iterator end,
                       unsigned int) 
{
  auto victim = fifo.front();
  memory.erase(victim);
  fifo.pop();
  return victim;
}

void FIFO::FIFOState::page_in(unsigned int location)
{
	memory.emplace(location);
	fifo.push(location);
}

const char* FIFO::name() const { return "FIFO"; }

std::unique_ptr<SwapScheduler::State> FIFO::make_state() const
{
	return std::make_unique<FIFOState>();
}
