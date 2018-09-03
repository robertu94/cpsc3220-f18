
CC=clang
CFLAGS=-Wall -g


BINS=sem mybank pthreadex sequential pthreadex2 sequential2 mystery readwritelockex
all: $(BINS)
echo:
	@echo $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $? -pthread

mybank: interactivebank.c bank.o
	$(CC) $(CFLAGS) -o $@ interactivebank.c bank.o -pthread

clean:
	rm -rf $(BINS) *.o *.dSYM

