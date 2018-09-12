#include "Scheduler.h"
class FIFOScheduler : public Scheduler
{
	public:
  virtual std::vector<TaskEvent> schedule(std::vector<Task> const& tasks) const override;
  
	virtual const char* name() const override;
};

