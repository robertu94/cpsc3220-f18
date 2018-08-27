#include <cstdlib>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>

//{{{ implementation details
typedef int (*mode_fn)(int, int);
mode_fn
get_command(const char* prog_mode)
{
	printf("mode=%s ", prog_mode);
	if (prog_mode == nullptr)
		return nullptr;
  else if (strncmp(prog_mode, "add", 3) == 0)
    return [](int l, int r) { return l + r; };
  else if (strncmp(prog_mode,"sub", 3) == 0)
    return [](int l, int r) { return l - r; };
  else
    return nullptr;
}
//}}}


mode_fn
get_mode_from_env()
{
  return get_command(getenv("TASK_ID"));
}

//{{{ Aside on returning vectors
// As of C++ 17, the following is _required_ to receive return value
// optimization which means that the vector is constructed in-place in the
// calling function.  Many compilers implemented this before c++17 at higher
// optimization levels. This is idea because it elides even moves.
//
// If you don't have either you can still take advantage of c++11 move semantics
// and returning a vector is then as cheap as returning a single pointer.  This
// is because the memory for the values of the vector are stored on the heap
// rather than the stack so only this pointer must be copied to "move" the
// object. The left over object is left in a valid, but undefined state.
// However, since we are returning imediatley after and the object is on the
// stack, it is will be destructed before it can be used again.
//
// Some may also quibble over the use of push_back rather than emplace_back,
// there is no substantive difference for so-called trivial types that are
// smaller than a quad word (64 bit value).
//}}}
std::vector<int>
get_values_from_argv(int argc, char* argv[])
{
  std::vector<int> values;
  values.reserve(argc - 1);
  // skip i=0 because it contains "child"
  for (int i = 1; i < argc; ++i) {
    values.push_back(std::atoi(argv[i]));
  }
  return values;
}

int
main(int argc, char* argv[])
{
  auto values = get_values_from_argv(argc, argv);
  auto mode = get_mode_from_env();
  if (mode == nullptr) {
    std::cout << "operation not supported" << std::endl;
    return -1;
  }

  std::cout << std::accumulate(std::begin(values), std::end(values), 0, mode)
            << std::endl;
  return 0;
}

// vim: foldmethod=marker
