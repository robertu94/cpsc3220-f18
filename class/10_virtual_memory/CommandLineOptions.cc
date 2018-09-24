#include "CommandLineOptions.h"
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <iomanip>
#include <unistd.h>

#include "Paging.h"
#include "Segmentation.h"
#include "MultiLevelPaging.h"

namespace {
enum class ProgramMode
{
  Segmentation,
  Paging,
	MultiLevelPaging
};

std::map<std::string, ProgramMode> str_to_mode{
  { "SEG", ProgramMode::Segmentation },
  { "PAGE", ProgramMode::Paging },
  { "2PAGE", ProgramMode::MultiLevelPaging },
};

void
usage()
{
  std::cerr << "./virtual_memory_test -p PHYSICAL_BITS -v VIRTUAL_BITS -o "
               "OFFSET_BITS -s SEGMENT_FILE -t PAGE_TABLE_FILE MODE ADDRESS "
            << std::endl;
}

} // namespace

CommandLineOptions
ParseOptions(int argc, char* argv[])
{
  CommandLineOptions cl_options;
  VirtualMemoryOptions vm_options;

  int opt;
  while ((opt = getopt(argc, argv, "hp:v:o:s:t:")) != -1) {
    switch (opt) {
      case 'h':
        usage();
        exit(EXIT_SUCCESS);
      case 'p':
        vm_options.physical_bits = atoi(optarg);
        break;
      case 'v':
        vm_options.virtual_bits = atoi(optarg);
        break;
      case 'o':
        vm_options.offset_bits = atoi(optarg);
        break;
      case 's':
        vm_options.segment_file = optarg;
        break;
      case 't':
        vm_options.page_table_file = optarg;
        break;
      default:
        usage();
        exit(EXIT_FAILURE);
    }
  }

  if (optind >= argc) {
    std::cerr << "Expected an ADDRESS and a MODE" << std::endl;
    usage();
    exit(EXIT_FAILURE);
  }

  try {
    auto& mode = str_to_mode.at(argv[optind++]);
    switch (mode) {
      case ProgramMode::Segmentation:
        cl_options.vmem = std::make_unique<Segmentation>(vm_options);
        break;
      case ProgramMode::Paging:
        cl_options.vmem = std::make_unique<Paging>(vm_options);
        break;
			case ProgramMode::MultiLevelPaging:
				cl_options.vmem = std::make_unique<MultiLevelPaging>(vm_options);
				break;
    }

  } catch (std::out_of_range& ex) {
    throw std::runtime_error("invalid mode");
  }

	std::istringstream ss{argv[optind++]};
  ss >> std::hex >> cl_options.address;
  cl_options.vm_options = vm_options;

  return cl_options;
}

