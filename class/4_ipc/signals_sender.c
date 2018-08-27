#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void sigchild_handler(int, siginfo_t*, void*);

void register_signal_handler()
{
	//register the sigchild_handler
	struct sigaction action,old_action;
	action.sa_sigaction = sigchild_handler;
	action.sa_flags = SA_RESTART|SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaction(SIGCHLD, &action, &old_action);
	printf("previous handler was: %s\n", ((old_action.sa_handler==SIG_DFL)?("default"):("not default")));

}

void do_signal(pid_t pid)
{
	int status = 0;


	//wait for the child to stop him/herself
	waitpid(pid, &status, WUNTRACED);
	
	//tell the child to wake him/herself backup
	printf("waiking up\n");
	kill(pid, SIGCONT);

	//ask the child to call the SIGUSR1 handler
	int second_to_sleep = 3;
	while(second_to_sleep = sleep(second_to_sleep));

	printf("sending singal\n");
	kill(pid, SIGUSR1);

	//wait for the child to exit
	bool done=false;
	while(!done)
	{
		waitpid(pid, &status, 0);
		done = WIFEXITED(status);
	}

	//report the return code of the child process
	int child_return_code = WEXITSTATUS(status);
	printf("done %d\n", child_return_code);
}

//{{{ sigchild_handler prints out what the child did
void sigchild_handler(int signal, siginfo_t* info, void* context) 
{
	const char* msg;
	size_t len;
	const char exited[] = "got sigchild: exited\n";
	const char stopped[] = "got sigchild: stopped\n";
	const char other[] = "got sigchild: other\n";
	const char continued[] = "got sigchild: continued\n";
	const char trapped[] = "got sigchild: trapped\n";
	const char killed[] = "got sigchild: killed\n";
	const char dumped[] = "got sigchil: dumped\n";

	switch(info->si_code)
	{
		case CLD_EXITED:
			len = sizeof(exited);
			msg = exited;
			break;
		case CLD_STOPPED:
			len = sizeof(stopped);
			msg = stopped;
			break;
		case CLD_TRAPPED:
			len = sizeof(trapped);
			msg = trapped;
			break;
		case CLD_CONTINUED:
			len = sizeof(continued);
			msg = continued;
			break;
		case CLD_KILLED:
			len = sizeof(killed);
			msg = killed;
			break;
		case CLD_DUMPED:
			len = sizeof(dumped);
			msg = dumped;
			break;
		default:
			len = sizeof(other);
			msg = other;
			break;
	}

	write(0, msg, len);

}
//}}}
//{{{main
int main(int argc, char *argv[])
{
	register_signal_handler();
	pid_t pid = fork();
	char* argv_child[] = {"./signals_reciever", NULL};
	switch(pid){
		case 0:
			execvp("./signals_reciever", argv_child);
			perror("exec failed\n");
			exit(1);
		case -1:
			perror("fork failed\n");
			exit(2);
		default:
			do_signal(pid);
	}
	wait(NULL);
	return 0;
}
//}}}

// vim: foldmethod=marker :

