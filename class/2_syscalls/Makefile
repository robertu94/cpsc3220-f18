ALL= hello_world hello_world_cpp shim_test shim.so shim_cpp.so shim_test_static hello_world_syscall hello_world_syscall_asm rawsyscall #shim_cpp_clang 
CFLAGS+=-O3 -Wall -Werror -Wextra
CXXFLAGS+=$(CFLAGS) -std=c++11 -fno-exceptions -fno-rtti

.PHONY: all strip clean
all: $(ALL)
strip: $(ALL)
	strip $(ALL)
clean:
	$(RM) $(ALL) $(wildcard *.o)

shim_test_static: CFLAGS+=-static

shim.so: shim.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $< -ldl

shim_cpp.so: shim_cpp.cc
	$(CXX) $(CXXFLAGS) -fPIC -shared -o $@ $< -ldl


# Requires newer clang than provided by the lab machines
# shim_cpp_clang: LDFLAGS+=-ldl -shared
# shim_cpp_clang: CXXFLAGS+=-fPIC -stdlib=libc++
# shim_cpp_clang: CXX=clang++

rawsyscall.o: rawsyscall.s
	$(CC) -c $^
rawsyscall: rawsyscall.o
	$(LD) $^ -o $@
