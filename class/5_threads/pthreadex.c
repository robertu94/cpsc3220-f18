#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define BIG 100000000L

unsigned long counter = 0;
pthread_mutex_t my_lock = PTHREAD_MUTEX_INITIALIZER;

void count_to_big()
{
	for (int i=0; i < BIG; i++)
	{
		pthread_mutex_lock(&my_lock);
		counter++;
		pthread_mutex_unlock(&my_lock);
	}
}

void * my_thread_func (void *arg)
{
	count_to_big();
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t t[2];

	pthread_create(&t[0], NULL, my_thread_func, NULL);
	pthread_create(&t[1], NULL, my_thread_func, NULL);

	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);

	printf("\nCounter=%lu\n",counter);
	return 0;
}