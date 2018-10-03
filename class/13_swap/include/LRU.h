#include "SwapScheduler.h"

#include <map>
#include <utility>
#include <boost/heap/binomial_heap.hpp>

class LRU : public SwapScheduler
{
  using SwapScheduler::SwapScheduler;

	const char* name() const override;

	class LRUState : public State {
		bool in_memory(unsigned int location) const override;
		unsigned int in_use() const override;
		unsigned int evict(std::vector<Request>::iterator, std::vector<Request>::iterator, unsigned int) override;
		void present(unsigned int location) override;
		void request_done(unsigned int) override;
		void page_in(unsigned int) override;


		private:
			// heap of (age -> location) that supports update_key style operations
			boost::heap::binomial_heap<std::pair<unsigned int, unsigned int>> last_used; 
			// map of (locations -> handle)
			std::map<unsigned int, decltype(last_used)::handle_type> in_lru;
			unsigned int age = 0; // age does not represent a time, last count of access
	};

	std::unique_ptr<State> make_state() const override;

};
