//threadtest.c

#include <stdio.h>
#include <stdlib.h>
#include "mythreads.h"


void *t1 (void *arg)
{
	int param = *((int*)arg);
	printf("t1 started %d\n",param);

	threadYield();

	int* result = malloc(sizeof(int));
	*result = param + 1;
	printf ("added 1! (%d)\n",*result);
	
	threadYield();

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

	id1 = threadCreate(t1,(void*)&p1);
	printf("created thread 1.\n");	
	
	id2 = threadCreate(t1,(void*)&p2);
	printf("created thread 2.\n");

	

	threadJoin(id1, (void*)&result1);
	printf("joined #1 --> %d.\n",*result1);

	threadJoin(id2, (void*)&result2);
	printf("joined #2 --> %d.\n",*result2);

}

