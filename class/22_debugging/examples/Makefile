CXXFLAGS+=-fopenmp -O3 -g -fno-omit-frame-pointer

.PHONY: false clean all

all: false1 false2
clean:
	$(RM) false1 false2 perf.data perf.data.old

false1: false1.cc sizes.h
false2: false2.cc sizes.h

