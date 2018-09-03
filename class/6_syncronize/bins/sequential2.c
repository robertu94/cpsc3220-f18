#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define BIG 2000000000L

unsigned long counter = 0;

void count_to_big()
{
	printf("Counting rapidly...\n");
	for (long i=0; i < BIG; i++)
	{ counter++;}
	printf("Counting rapidly...done\n");
}



void do_something_really_slow()
{
	for (int i=0; i < 10; i++)
	{
		printf("Counting slowly...%d\n",i);
		sleep(1);
	}
}


int main(int argc, char **argv)
{
	count_to_big();
	do_something_really_slow();
	printf("\nCounter=%lu\n",counter);
	return 0;
}