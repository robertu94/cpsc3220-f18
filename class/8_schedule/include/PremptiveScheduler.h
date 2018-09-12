#pragma once
#include "Scheduler.h"

class PremptiveScheduler : public Scheduler
{
	public:
	PremptiveScheduler(std::size_t quanta): Scheduler(), quanta(quanta) {}

	protected:
	std::size_t quanta;
};

