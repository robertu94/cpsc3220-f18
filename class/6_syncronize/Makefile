CC=clang
CFLAGS=-Wall -g
CXXFLAGS=-std=c++14
LDFLAGS=-pthread


BINS= conditionex readwritelockex sem \
			hello_world_atomics reader_writer condition_variable
.PHONY: all bins
all: $(BINS) bins
bins:
	$(MAKE) -C bins
echo:
	@echo $(BINS)

clean:
	rm -rf $(BINS) $(wildcard *.o)
	$(MAKE) -C bins clean


