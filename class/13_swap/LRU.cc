#include "LRU.h"

bool LRU::LRUState::in_memory(unsigned int location) const {
	return in_lru.find(location) != in_lru.end();
}

unsigned int LRU::LRUState::in_use() const {
	return in_lru.size();
}

unsigned int LRU::LRUState::evict(std::vector<Request>::iterator, std::vector<Request>::iterator, unsigned int) {
		auto victim = last_used.top();
		last_used.pop();
		return victim.second;
}

void LRU::LRUState::page_in(unsigned int location) 
{
	in_lru[location] = last_used.emplace(age, location);
}

void LRU::LRUState::present(unsigned int location) 
{
	last_used.increase(in_lru[location], {age, location});
}

void LRU::LRUState::request_done(unsigned int) {
	++age;
}

const char* LRU::name() const { return "LRU"; }

std::unique_ptr<SwapScheduler::State>
LRU::make_state() const
{
  return std::make_unique<LRUState>();
}
