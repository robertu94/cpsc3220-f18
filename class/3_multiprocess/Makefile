ALL=hello_worlds for_a_fist_full_of_syscalls for_a_few_syscalls_more a_syscall_to_die_for fork_bomb child ptrace_example
.PHONY: all clean
CXXFLAGS+=-std=c++11
all: $(ALL)
clean:
	$(RM) $(ALL)
docker:
	sudo docker build -t fork_bomb .
	sudo docker run -m 1g fork_bomb
