#include <iosfwd>

#include "Commandline.h"

struct Request
{
  unsigned int arrival_time;
  unsigned int location;
  static bool SortByArrivalTime(Request const& lhs, Request const& rhs);
  static bool SortByLocation(Request const& lhs, Request const& rhs);
};


std::ostream&
operator<<(std::ostream& out, Request const& request);

std::vector<Request>
generate_requests(CommandLine::Options const& options);

struct SwapEvent
{
  enum class EventType
  {
    PageOut,
    PageIn,
    Reference,
  } type;
  unsigned int location;
  SwapEvent(EventType type, unsigned int location)
    : type(type)
    , location(location)
  {}
};

std::ostream&
operator<<(std::ostream& out, SwapEvent const&);

std::ostream&
operator<<(std::ostream& out, SwapEvent::EventType const&);
