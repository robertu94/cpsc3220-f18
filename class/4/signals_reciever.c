#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

static bool done = false;

void sigusr1_handler(int signal_number)
{
	const char msg[] = "sigusr1 called\n";
	write(0, msg, sizeof(msg));
	done=true;
}

int main(int argc, char *argv[])
{
	

	//why don't we see duplicate messages here?
	printf("sending self sigchld\n");
	kill(getpid(), SIGCHLD);

	//register sigur1 action
	signal(SIGUSR1, sigusr1_handler);

	//tell parent we are ready by stopping ourself
	kill(getpid(), SIGSTOP);

	//our parent will wake us up
	while(!done)
	{
		printf("waiting to get usr1\n");
		sleep(1);
	}
	printf("child done\n");



	return 0;
}
