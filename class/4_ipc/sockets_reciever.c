#include <sys/socket.h>
#include <signal.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

bool done = false;
const int backlog = 10;
const char address[] = "unix_socket";

void sigint_handler(int signal)
{
	done = true;
}

void client(int client_fd)
{
	const int buf_size = 100;
	char buf[buf_size];
	int read_len = read(client_fd, buf, buf_size);
	if(read_len < buf_size) buf[read_len] = '\0';
	else  buf[buf_size-1] = '\0';

	printf("got %s\n", buf);
	shutdown(client_fd, SHUT_RDWR);
	close(client_fd);
}

int main(int argc, char *argv[])
{
	//{{{configure signal to trigger cleanup
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0; /* we want EINTR, so do not set SA_RESTART */
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	//}}}

	int listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	//{{{error handling
	if(listen_fd == -1){
		perror("failed to open socket");
		exit(1);
	}
	//}}}

	struct sockaddr_un listen_addr, client_addr;
	memset(&listen_addr, 0, sizeof(struct sockaddr_un));
	listen_addr.sun_family = AF_UNIX;
	strncpy(listen_addr.sun_path, address, sizeof(listen_addr.sun_path));

	int ret;
	ret = bind(listen_fd, (struct sockaddr*)&listen_addr, sizeof(struct sockaddr_un));
	//{{{error handling
	if(ret == -1)
	{
		perror("failed to bind socket");
		close(listen_fd);
		exit(1);
	}
	//}}}

	ret = listen(listen_fd, backlog);
	//{{{error handling
	if(ret == -1)
	{
		perror("failed to listen");
		close(listen_fd);
		exit(1);
	}
	//}}}

	socklen_t peer_size = sizeof(struct sockaddr_un); 
	while(!done)
	{
		int client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &peer_size);
		if(client_fd != -1)
		{
			client(client_fd);
		} else {
			//handle accept errors {{{
			extern int errno;
			if(errno != EINTR)
			{
				//we were not interupted so something else went wrong
				perror("failed to accept client");
			}
		  //}}}
		}
	}

	close(listen_fd);
	remove(address);

	return 0;
}
// vim: foldmethod=marker :
