#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#define BIG 100000000L


unsigned long counter = 0;

void count_to_big()
{
	for (int i=0; i < BIG; i++)
	{
		counter++;
	}
}


int main(int argc, char **argv)
{
	count_to_big();
	count_to_big();
	printf("\nCounter=%lu\n",counter);
	return 0;
}