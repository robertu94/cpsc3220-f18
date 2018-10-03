#pragma once

#include <vector>
#include <memory>

#include "Request.h"

class SwapScheduler
{
public:
  SwapScheduler(unsigned int memory_size);

	//
	// Determine a ordering of PageIn/PageOut actions
	//
	// post: the request array is not modified (why passed by value)
	//
  std::vector<SwapEvent> schedule(std::vector<Request> requests);
	virtual const char* name() const=0;
  virtual ~SwapScheduler() = default;

protected:
  unsigned int memory_size;

	//sub-classed in each subclass to contain the data of the class
	class State
	{
		public:

		virtual ~State()=default;
		//
		// checks if a key is present in state
		//
		virtual bool in_memory(unsigned int location) const=0;

		//
		// returns the number of items in memory
		//
		virtual unsigned int in_use() const=0;


		//
		// evicts a element from memory based on its policy 
		//
		// pre: memory is full
		// post: State is updated to reflect element is evicted
		// return: memory location to evict
		//
		virtual unsigned int evict(std::vector<Request>::iterator request, std::vector<Request>::iterator end, unsigned int memory_size)=0;

		//
		// inserts a element into memory
		//
		// post: State is updated to reflect element being paged in
		//
		virtual void page_in(unsigned int location)=0;

		//
		// called when an element is present in cache
		//
		virtual void present(unsigned int location);

		//
		// called when an request is completed processing
		//
		virtual void request_done(unsigned int location);
	};

private:

	
	virtual std::unique_ptr<State> make_state() const=0;
};
