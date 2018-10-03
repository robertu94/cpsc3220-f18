#include "SwapScheduler.h"
#include <set>
#include <queue>

class FIFO : public SwapScheduler
{
  using SwapScheduler::SwapScheduler;

	class FIFOState : public State {
		bool in_memory(unsigned int location) const override ;
		unsigned int in_use() const override;
		unsigned int evict(std::vector<Request>::iterator request, std::vector<Request>::iterator end, unsigned int) override;
		void page_in(unsigned int) override;

    std::set<unsigned int> memory;
    std::queue<unsigned int> fifo;
	};

	const char* name() const override;

	std::unique_ptr<State> make_state() const override;
};
