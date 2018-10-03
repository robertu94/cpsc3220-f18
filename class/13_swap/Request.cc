#include "Request.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>


bool Request::SortByArrivalTime(Request const& lhs, Request const& rhs)
{
	return lhs.arrival_time < rhs.arrival_time;
}

bool Request::SortByLocation(Request const& lhs, Request const& rhs)
{
	return lhs.location < rhs.location;
}

std::ostream&
operator<<(std::ostream& out, Request const& request)
{
  return out << request.arrival_time << '\t' << request.location;
}

std::vector<Request>
generate_requests(CommandLine::Options const& options)
{
  std::vector<Request> requests;
  std::seed_seq seed{ options.seed };
  std::mt19937 gen{ seed };
  std::uniform_int_distribution<int> location_dist(0, options.memory_sections);
  std::poisson_distribution<int> arrival_dist(options.duration);

  std::generate_n(std::back_inserter(requests), options.num_requests,
                  [&location_dist, &arrival_dist, &gen]() {
                    Request request;
                    request.location = location_dist(gen);
                    request.arrival_time = arrival_dist(gen);
                    return request;
                  });

  std::sort(std::begin(requests), std::end(requests),
            Request::SortByArrivalTime);

  return requests;
}

std::ostream&
operator<<(std::ostream& out, SwapEvent::EventType const& et)
{
	switch(et)
	{
		case SwapEvent::EventType::PageIn:
			return out << "Page In";
		case SwapEvent::EventType::PageOut:
			return out << "Page Out";
		case SwapEvent::EventType::Reference:
			return out << "Referenced";
	}
}

std::ostream&
operator<<(std::ostream& out, SwapEvent const& event)
{
	return out << event.type << " " << event.location;
}


