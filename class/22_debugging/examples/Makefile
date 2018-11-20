CXX=clang++
CXXFLAGS+=-std=c++14 -fno-omit-frame-pointer
OMPFLAGS=-fopenmp -g

.PHONY: false clean all

all: false1 false2 work pi_mpi pi_mp pi_std
clean:
	$(RM) false1 false2 perf.data perf.data.old

false1: CXXFLAGS+=$(OMPFLAGS)
false1: false1.cc

false2: CXXFLAGS+=$(OMPFLAGS)
false2: false2.cc

pi_mpi: CXX=mpic++
pi_std: LDFLAGS=-lpthread

