#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define BIG 2000000000L

unsigned long counter = 0;
int we_are_done = 0;

void count_to_big()
{
	printf("Counting rapidly...\n");
	for (long i=0; i < BIG; i++)
	{ counter++;}
	printf("Counting rapidly...done\n");
}



void do_something_really_slow()
{
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	for (int i=0; i < 10; i++)
	{
		//if (we_are_done) pthread_exit(NULL);
		printf("Counting slowly...%d\n",i);

		if (i > 6)
		{
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
		}
		sleep(1);
		
	}
}



void *my_thread_func (void *param)
{
	do_something_really_slow();
	return NULL;
}


int main(int argc, char **argv)
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, my_thread_func, NULL);
	pthread_create(&t2, NULL, my_thread_func, NULL);

	count_to_big();

	//we_are_done = 1;
	pthread_cancel(t1);
	pthread_join(t1, NULL);
	pthread_join(t2,NULL);
	printf("\nCounter=%lu\n",counter);
	return 0;
}