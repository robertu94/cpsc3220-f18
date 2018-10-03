#include "SwapScheduler.h"

class OPT : public SwapScheduler
{
	class OPTState : public State {
		bool in_memory(unsigned int location) const override;
		unsigned int in_use() const override;
		unsigned int evict(std::vector<Request>::iterator request, std::vector<Request>::iterator end, unsigned int memory_size) override;
		void page_in(unsigned int) override;

		std::set<unsigned int> memory;
		unsigned int memory_size;
	};

	std::unique_ptr<State> make_state() const override;
	const char* name() const override;

  using SwapScheduler::SwapScheduler;

};

