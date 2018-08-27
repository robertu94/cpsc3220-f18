#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

const int backlog = 10;
const char address[] = "unix_socket";


int main(int argc, char *argv[])
{
	if(argc != 2) {
		fprintf(stderr, "USAGE: ./sockets_sender \"message to send\"");
		exit(EXIT_FAILURE);
	}

	int ret;
	int client_fd = socket(AF_UNIX, SOCK_STREAM, 0);

	struct sockaddr_un client_addr;
	memset(&client_addr, 0, sizeof(struct sockaddr_un));
	client_addr.sun_family = AF_UNIX;
	strncpy(client_addr.sun_path, address, sizeof(client_addr.sun_path));

	ret = connect(client_fd, (struct sockaddr*)&client_addr, sizeof(struct sockaddr_un));
	//{{{error handling
	if(ret)
	{
		close(client_fd);
		perror("failed to connect");
		exit(1);
	}
	//}}}

	const int len = strlen(argv[1])+1;
	ret = send(client_fd, argv[1], len, /*flags=*/0);
	//{{{error handling
	if(ret == -1)
	{
		perror("failed to send");
		shutdown(client_fd, SHUT_RDWR);
		close(client_fd);
		exit(1);
	}
	//}}}


	shutdown(client_fd, SHUT_RDWR);
	close(client_fd);

	return 0;
}

// vim: foldmethod=marker :
