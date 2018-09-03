CC=clang
CFLAGS=-Wall -g -std=c11
CXXFLAGS=-std=c++14
LDFLAGS=-pthread


BINS=pthreadex sequential pthreadex2 sequential2 \
		 hello_world_lite_cpp hello_world_wrong std_async_async std_async_defered
all: $(BINS)
echo:
	@echo $(BINS)

clean:
	rm -rf $(BINS) $(wildcard *.o)

