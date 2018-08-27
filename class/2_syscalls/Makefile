ALL= hello_world hello_world_cpp shim_test shim shim_cpp shim_cpp_clang shim_test_static hello_world_syscall hello_world_syscall_asm rawsyscall
CFLAGS+=-O3 -Wall -Werror -Wextra
CXXFLAGS+=$(CFLAGS) -std=c++11 -fno-exceptions -fno-rtti

.PHONY: all strip clean
all: $(ALL)
strip: $(ALL)
	strip $(ALL)
clean:
	$(RM) $(ALL) $(wildcard *.o)

shim_test_static: CFLAGS+=-static

shim: LDFLAGS+=-ldl -shared
shim: CFLAGS+=-fPIC

shim_cpp: LDFLAGS+=-ldl -shared
shim_cpp: CXXFLAGS+=-fPIC

shim_cpp_clang: LDFLAGS+=-ldl -shared
shim_cpp_clang: CXXFLAGS+=-fPIC -stdlib=libc++
shim_cpp_clang: CXX=clang++

rawsyscall.o: rawsyscall.s
	$(CC) -c $^
rawsyscall: rawsyscall.o
	$(LD) $^ -o $@
