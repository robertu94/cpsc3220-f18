BINS= named_pipe_reciever named_pipe_sender \
			pipes signals_reciever shmem_mmap shmem_sysv \
			signals_sender sockets_reciever sockets_sender \
			msgpassing_client msgpassing_server

GARBAGE=unix_socket
.PHONY: all clean
all: $(BINS)
clean:
	$(RM) $(BINS) $(GARBAGE)


