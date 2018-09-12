#include "PremptiveScheduler.h"

class RRScheduler : public PremptiveScheduler
{
	
	public:
		using PremptiveScheduler::PremptiveScheduler;

  virtual std::vector<TaskEvent> schedule(
    std::vector<Task> const& tasks) const override;
	virtual const char* name() const override;
};
