#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <vector>

namespace CommandLine {
using namespace std::string_literals;
enum class FitMode
{
  BestFit,
  WorstFit,
  FirstFit
};

enum class InputMode
{
  FromFile,
  Generate
};

const std::map<std::string, FitMode> modes{
  { "best"s, FitMode::BestFit },
  { "first"s, FitMode::FirstFit },
  { "worst"s, FitMode::WorstFit },
};

struct Options
{
  std::string file_path = "allocations";
  int seed = 0;
  int num_generate = 10;
  int num_requests = 10;
  int page_size = 4096;
  std::size_t physical_memory_size = page_size * num_generate * num_generate;
  FitMode fit_mode = FitMode::BestFit;
  InputMode input_mode = InputMode::Generate;
};

void
usage()
{
  std::cout << "./dynamic_storage -f <ALLOCATION_FILE> -p <PHYSICAL MEM SIZE> "
               "-n <NUM_GENERATE> -r <NUM_REQUESTS> MODE"
            << std::endl;
}

std::shared_ptr<Options>
parse_args(int argc, char* argv[])
{
  auto options = std::make_shared<Options>();
  int opt;

  while ((opt = getopt(argc, argv, "f:n:p:r:")) != -1) {
    switch (opt) {
      case 'f':
        options->input_mode = InputMode::FromFile;
        options->file_path = optarg;
        break;
      case 'p':
        options->physical_memory_size = std::strtoull(optarg, nullptr, 10);
        break;
      case 'n':
        options->num_generate = std::strtoull(optarg, nullptr, 10);
        break;
      case 'r':
        options->num_requests = std::strtoull(optarg, nullptr, 10);
        break;
      default:
        usage();
        exit(EXIT_FAILURE);
    }
  }

  if (optind > argc) {
    usage();
    exit(EXIT_FAILURE);
  }
  options->fit_mode = modes.at(argv[optind++]);
  return options;
}
} // namespace CommandLine

struct Allocation
{
  Allocation()
    : ptr(0)
    , size(0)
  {}
  Allocation(std::uint64_t ptr, std::size_t size)
    : ptr(ptr)
    , size(size)
  {}
  std::uint64_t ptr;
  std::size_t size;

  static bool SortByPtrSize(Allocation const& left, Allocation const& right)
  {
    if (left.ptr < right.ptr)
      return true;
    else if (left.ptr == right.ptr)
      return left.size < right.size;
    else
      return false;
  }
  static bool SortBySize(Allocation const& left, Allocation const& right)
  {
    return left.ptr < right.ptr;
  }
};

std::istream&
operator>>(std::istream& in, Allocation& alloc)
{
  return in >> alloc.ptr >> alloc.size;
}

std::ostream&
operator<<(std::ostream& out, Allocation const& alloc)
{
  return out << alloc.ptr << " " << alloc.size;
}

auto
read_alloctions_from_file(std::shared_ptr<CommandLine::Options> options)
{
  std::vector<Allocation> allocs;
  std::ifstream file(options->file_path);

  while (file.good()) {
    Allocation alloc;
    file >> alloc;
    allocs.emplace_back(alloc);
  }

  return allocs;
}

class InsufficentSpace : public std::exception
{
public:
  const char* what() const noexcept { return "insufficient space to allocate"; }
};

class Allocator
{
public:
  Allocator(std::vector<Allocation> allocs,
            std::shared_ptr<CommandLine::Options> options)
    : options(options)
    , allocs(allocs)
  {
    std::sort(std::begin(this->allocs), std::end(this->allocs),
              Allocation::SortByPtrSize);
  }
  virtual ~Allocator() = default;

  /*
   * Preforms an allocation, or throws InsufficentSpace if it fails
   *
   * Returns: address of the begining of the allocation
   */
  std::uint64_t allocate(std::size_t size)
  {
    auto regions = free_regions();

    // remove regions that wont fit the allocation
    regions.erase(std::remove_if(std::begin(regions), std::end(regions),
                                 [size](Allocation const& region) {
                                   return region.size < size;
                                 }),
                  std::end(regions));

    if (regions.empty()) {
      throw InsufficentSpace();
    }
    auto ptr = do_allocate(size, regions);

    allocs.emplace_back(ptr, size);

    return ptr;
  }

  void deallocate(std::uint64_t ptr)
  {
    allocs.erase(std::remove_if(
                   std::begin(allocs), std::end(allocs),
                   [ptr](Allocation const& alloc) { return alloc.ptr == ptr; }),
                 std::end(allocs));
		std::sort(std::begin(allocs), std::end(allocs), Allocation::SortByPtrSize);
  }

  std::vector<Allocation> get_allocations() const { return allocs; }

protected:
  std::shared_ptr<CommandLine::Options> options;
  std::vector<Allocation> allocs;

  /*
   * Returns a list of the regions that can be allocated from
   *
   * Post: return value is non-empty
   */
  std::vector<Allocation> free_regions() const
  {
    std::vector<Allocation> regions;

    // insert a dummy head and tail value when computing free regions
    // this ensures we always have at least two regions "allocated" which
    // simplifies the math below
    std::vector<Allocation> allocs_with_head_tail = allocs;
    allocs_with_head_tail.emplace_back(0, 0);
    allocs_with_head_tail.emplace_back(options->physical_memory_size, 0);
    std::sort(std::begin(allocs_with_head_tail),
              std::end(allocs_with_head_tail), Allocation::SortByPtrSize);

    {
      auto end = std::end(allocs_with_head_tail);
      auto current = std::begin(allocs_with_head_tail);
      auto next = std::next(current);
      for (; next != end; ++current, ++next) {
        auto end_loc = current->ptr + current->size;

        regions.emplace_back(end_loc, next->ptr - end_loc);
      }
    }

    return regions;
  }

private:
  /*
   * Preforms the actual allocation, overwritten by strategy classes below
   *
   * Pre: for all region in regions, region.size >= size
   */
  virtual std::uint64_t do_allocate(std::size_t size,
                                    std::vector<Allocation> const& regions) = 0;
};

struct BestFit : public Allocator
{
public:
  using Allocator::Allocator;

  std::uint64_t do_allocate(std::size_t size,
                            std::vector<Allocation> const& free_list) override
  {
    auto best_fit = std::min_element(std::begin(free_list), std::end(free_list),
                                     Allocation::SortBySize);
    return best_fit->ptr;
  }
};

struct WorstFit : public Allocator
{
public:
  using Allocator::Allocator;

  std::uint64_t do_allocate(std::size_t size,
                            std::vector<Allocation> const& free_list) override
  {
    auto worst_fit = std::max_element(
      std::begin(free_list), std::end(free_list), Allocation::SortBySize);
    return worst_fit->ptr;
  }
};

struct FirstFit : public Allocator
{
public:
  using Allocator::Allocator;

  std::uint64_t do_allocate(std::size_t size,
                            std::vector<Allocation> const& free_list) override
  {
    return free_list.front().ptr;
  }
};

auto
generate_allocs(std::shared_ptr<CommandLine::Options> options)
{
  std::vector<Allocation> allocs;
  std::seed_seq seed{ options->seed };
  std::mt19937 gen{ seed };
  std::uniform_int_distribution<std::uint64_t> size_dist{ 1, 4096 };
  std::uniform_int_distribution<std::uint64_t> placement_dist{ 0, options->physical_memory_size };

	for(int i = 0; i < options->num_generate ; ++i)
	{
			std::sort(std::begin(allocs), std::end(allocs), Allocation::SortByPtrSize);
			for (int retries = 0; retries < 3; ++retries) {
				Allocation alloc{ placement_dist(gen), size_dist(gen) };
				auto prev = std::lower_bound(std::begin(allocs), std::end(allocs), alloc, Allocation::SortByPtrSize);

				assert(false);
				if(/*inserting first allocation*/);
				else if(/*inserting beginning*/);
				else if(/*insert after element if it fits*/);
				else if(/*insert at end*/);


			}
	}

  return allocs;
}

auto
generate_requests(std::shared_ptr<CommandLine::Options> options)
{
  std::vector<std::size_t> requests;
  std::seed_seq seed{ options->seed };
  std::mt19937 gen{ seed };
  std::uniform_int_distribution<std::uint64_t> size_dist{ 0, 4096 };

  std::generate_n(std::back_inserter(requests), options->num_requests,
                  [&size_dist, &gen]() { return size_dist(gen); });

  return requests;
}

int
main(int argc, char* argv[])
{
  using namespace CommandLine;
  auto args = parse_args(argc, argv);

  std::unique_ptr<Allocator> allocator;
  std::vector<Allocation> existing_allocs;

  switch (args->input_mode) {
    case InputMode::FromFile:
      existing_allocs = read_alloctions_from_file(args);
      break;
    case InputMode::Generate:
      existing_allocs = generate_allocs(args);
      break;
  }

  std::cout << "Ptr\tSize\t" << std::endl;
	for(auto const& alloc: existing_allocs)
	{
		std::cout << alloc << std::endl;
	}

  switch (args->fit_mode) {
    case FitMode::BestFit:
      allocator = std::make_unique<BestFit>(existing_allocs, args);
      break;
    case FitMode::WorstFit:
      allocator = std::make_unique<BestFit>(existing_allocs, args);
      break;
    case FitMode::FirstFit:
      allocator = std::make_unique<BestFit>(existing_allocs, args);
      break;
  }

  std::vector<std::size_t> requests = generate_requests(args);

  std::cout << "Requests: ";
  std::copy(std::begin(requests), std::end(requests),
            std::ostream_iterator<std::size_t>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "Action\tPtr\tSize\t" << std::endl;
  for (auto request : requests) {
    try {
      auto result = allocator->allocate(request);
      std::cout << "Allocated\t" << result << std::endl;
    } catch (InsufficentSpace const& ex) {
      std::cout << ex.what() << " size: " << request << std::endl;
    }
  }
  return 0;
}
