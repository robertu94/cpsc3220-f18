#include "Scheduler.h"
#include <algorithm>
#include <iterator>

class LotteryScheduler : public Scheduler
{
	public:
  virtual std::vector<TaskEvent> schedule(
    std::vector<Task> const& tasks) const override;
	virtual const char* name() const override;
  
};


