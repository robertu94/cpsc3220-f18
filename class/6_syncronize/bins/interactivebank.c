#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "bank.h"

#define MAX_LINE 1024
#define TIME_LIMIT 10
#define FEE_AMT		45

char *get_line (char *, size_t);
int counter = 0;



void *my_thread_func (void *param)
{
	//do some monitoring in here
	while (1)
	{
		//grab lock
		counter++;
		if (counter >= TIME_LIMIT )
		{
			printf("Ha ha, no money for you. (-%d) \n",FEE_AMT);
			bank_do_command("withdraw",FEE_AMT);
			counter= 0;
		}
		//release lock
		sleep(1);
	}
	return NULL;
}




int main(int argc, char **argv)
{
	bank_init(0);

	pthread_t t;

	pthread_create(&t, NULL, my_thread_func, NULL);
	
	while (1)
	{
		char buffer[MAX_LINE+1];

		printf("prompt> ");
		fflush(stdout); //make sure the prompt shows up...probably unnecessary, but without it you don't have any guarantee that the prompt will be printed before scanf is called.
		
		//read command
		if (NULL == get_line(buffer, MAX_LINE)) break;

		//need to lock here
		counter = 0;

		//use strtok_r to make it thread safe
		char *saveptr;
		char *cmd = strtok_r(buffer, " ", &saveptr);
		if (cmd == NULL) continue;
		char *val = strtok_r(NULL, " ,\t\n", &saveptr);
		int value = (val != NULL ? atoi(val) : -1);

		//respond to commands
		int response;
		if ((response = bank_do_command(cmd,value)) != -1)
		{
			printf("Executed(%s). New balance = %d\n",cmd, response);
			continue;
		} 
		if (strcmp(cmd, "exit") == 0)
		{
			break;
		}
		
		if (strcmp(cmd, "help") == 0)
		{
			printf("Help for our bank account demo.\n"
					"\tFORMAT:\t\tcommand [value]\n\n"
					"\tRecognized commands:\n"
					"\tdeposit\t\tadd [value] dollars to the balance.\n"
					"\twithdraw\tsubtract [value] dollars from the balance.\n"
					"\tbalance\t\tprint out the current balance.\n"
					"\texit\t\tquit the program.\n\n");
			continue;
		}
		printf("Unrecognized command (cmd=%s, val=%d), try \"help\"\n",cmd,value);
		//unlock here, or do more fine-grained locking
		//if you want to sqeeze out a little more performance.
	}

	printf("Ok. we're done...\n");
			
	return 0;
}

char *get_line (char *buf, size_t bufsize)
{
  char *p = fgets (buf, bufsize, stdin);

  if (p != NULL) {
    size_t last = strlen (buf) - 1;

    if (buf[last] == '\n') buf[last] = '\0';
  }
  return p;
}

