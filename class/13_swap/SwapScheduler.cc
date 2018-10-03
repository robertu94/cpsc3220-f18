#include "SwapScheduler.h"


SwapScheduler::SwapScheduler(unsigned int memory_size) : memory_size(memory_size) {}

std::vector<SwapEvent> SwapScheduler::schedule(std::vector<Request> requests)
{
	std::sort(std::begin(requests), std::end(requests), Request::SortByArrivalTime);
	std::vector<SwapEvent> events;

	auto state = make_state();

	auto end = std::end(requests);
	for(auto request = std::begin(requests); request != end; ++request)
	{
		if(!state->in_memory(request->location))
		{
			if(state->in_use() >= memory_size)
			{
				auto victim = state->evict(request, end, memory_size);
				events.emplace_back(SwapEvent::EventType::PageOut, victim);
			}
			state->page_in(request->location);
			events.emplace_back(SwapEvent::EventType::PageIn, request->location);
		} else {
			state->present(request->location);
		}
		events.emplace_back(SwapEvent::EventType::Reference, request->location);
		state->request_done(request->location);
	} 	
	return events;
}

void SwapScheduler::State::request_done(unsigned int location) {}
void SwapScheduler::State::present(unsigned int location) {}
