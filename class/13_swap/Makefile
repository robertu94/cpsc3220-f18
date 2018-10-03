BINS=Swap
CXX=clang++
CPPFLAGS=-Iinclude/
CXXFLAGS=-std=c++14 -stdlib=libc++ -g

all: $(BINS)
clean:
	$(RM) $(BINS) $(wildcard *.o)
Swap: Swap.o OPT.o LRU.o FIFO.o Request.o SwapScheduler.o Commandline.o
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^
