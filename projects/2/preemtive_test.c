#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <string.h>
#include <unistd.h>
#include "mythreads.h"

#define BIG 1000
#define TIMER_INTERVAL_US 10

//this function will be called
//everytime that the timer fires
//...then I call yield.
void timer_handler (int signum) 
{
	if (!interruptsAreDisabled)
	{
		printf("--------->$$$$ interrupting\n");
		threadYield();
	}
} 

//setup the timer that will preempt your thread
//library
void set_timer()
{
	struct sigaction sa; 
	struct itimerval timer; 

	/* Install timer_handler as the signal handler for SIGVTALRM.  */ 
	memset (&sa, 0, sizeof (sa)); 
	sa.sa_handler = &timer_handler; 
	sigaction (SIGALRM, &sa, NULL); 

  	/* Configure the timer to expire after TIMER_INTERVAL_US usec...  */ 
	timer.it_value.tv_sec = 0; 
	timer.it_value.tv_usec = TIMER_INTERVAL_US; 

	/* ... and every TIMER_INTERVAL_US usec after that.  */ 
	timer.it_interval.tv_sec = 0; 
	timer.it_interval.tv_usec = TIMER_INTERVAL_US; 

  	/* Start a virtual timer. It counts down whenever this process is executing.  */ 
	if (0 != setitimer (ITIMER_REAL, &timer, NULL))
	{
		perror("setitimer error");
	} 
}

void *t1 (void *arg)
{
	int param = *((int*)arg);
	printf("t1 started %d\n",param);

	int* result = malloc(sizeof(int));
	
	*result = param;
	for (int i=0; i < (param * BIG); i++)
	{
		*result += 1;
	}

	
	printf ("finished with math! (%d)\n",*result);
	
	sleep(1);
	printf("t1: done result=%d\n",*result);
	return result;
}



int main(void)
{
	int id1, id2;
	int p1;
	int p2;

	p1 = 23;
	p2 = 2;

	int *result1, *result2;

	//initialize the threading library. DON'T call this more than once!!!
	threadInit();

	//I will always start the timer after threadInit
	set_timer();

	id1 = threadCreate(t1,(void*)&p1);
	printf("created thread 1.\n");	
	
	id2 = threadCreate(t1,(void*)&p2);
	printf("created thread 2.\n");

	

	threadJoin(id1, (void*)&result1);
	printf("joined #1 --> %d.\n",*result1);

	threadJoin(id2, (void*)&result2);
	printf("joined #2 --> %d.\n",*result2);

}

