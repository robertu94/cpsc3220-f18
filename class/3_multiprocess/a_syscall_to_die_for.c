#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void parent(pid_t child_pid)
{
	pid_t parent_pid  = getpid();
	printf("parent started %d\n", parent_pid);
	int status;
	sleep(3);
	kill(child_pid, SIGSTOP);
	printf("child stopped %d\n", child_pid);
	sleep(3);
	kill(child_pid, SIGCONT);
	printf("child restarted %d\n", child_pid);
	sleep(3);
	kill(child_pid, SIGTERM);
	printf("child terminated %d\n", child_pid);
	kill(child_pid, SIGKILL);
	printf("child killed %d\n", child_pid);
	waitpid(child_pid, &status, 0);
	printf("parent done\n");

}

void child()
{
	pid_t child_pid  = getpid();
	signal(SIGTERM, SIG_IGN);
	signal(SIGKILL, SIG_IGN);
	perror("sigkill");
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
			parent(pid);
	}
	return 0;
}
