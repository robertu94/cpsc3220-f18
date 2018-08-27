#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const int read_end = 0, write_end = 1;

void child(int write_pipe, const char* message)
{
	write(write_pipe, message, strlen(message)+1);
	close(write_pipe);
}

void parent(int read_pipe, pid_t child)
{
	const int buf_size = 4096;
	char buf[buf_size];
	int len_read = read(read_pipe, buf, buf_size);
	buf[len_read-1] = '\n';
	write(STDOUT_FILENO, buf, len_read);
	wait(NULL);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		
		exit(EXIT_FAILURE);
	}
	int ret;
  int pipefds[2];
	ret = pipe(pipefds);
	//{{{ error handling
	if(ret == -1)
	{
		std::perror("failed to create pipe");
		exit(EXIT_FAILURE);
	}
	//}}}

	pid_t pid = fork();
	switch(pid){
		case -1:
			std::perror("failed to fork");
			exit(1);
			break;
		case 0:
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			close(STDIN_FILENO);
			close(pipefds[read_end]);
			child(pipefds[write_end], argv[1]);
			break;
		default:
			close(pipefds[write_end]);
			parent(pipefds[read_end], pid);
			break;
	}
	return 0;
}

// vim: foldmethod=marker :
