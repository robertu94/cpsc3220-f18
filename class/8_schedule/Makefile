CXX=clang++
CXXFLAGS=-std=c++14 -Wall -Werror -Wextra -g -Iinclude
OBJS = scheduler_test.o Scheduler.o SJF.o FIFO.o STCF.o RR.o Lottery.o EDF.o


.PHONY: clean
scheduler_test:  $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^
clean:
	$(RM) $(OBJS)
