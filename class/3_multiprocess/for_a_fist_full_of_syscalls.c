#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


int global = 3;
void parent(pid_t child_pid)
{
	pid_t parent_pid  = getpid();
	printf("parent started %d\n", parent_pid);
	int status;
	waitpid(child_pid, &status, 0);
	printf("parent done\n");

}

void child()
{
	pid_t child_pid  = getpid();
	printf("child started %d\n", child_pid);
	for (int i = 0; i < 10; ++i) {
		sleep(1);
		printf("child %d\n", i);

	}
	printf("child done\n");
}

int main(int argc, char *argv[])
{
	pid_t pid = fork();
	switch(pid)
	{
		case 0:
			child();
			break;
		case -1:
			perror("failed to fork\n");
			exit(1);
		default:
			global = 4;
			parent(pid);
	}
	printf("%d\n", global);
	return 0;
}
