#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
//#include <unistd.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
long counter = 0;

void *thread1func (void *param)
{
	for (int i=0; i < 1000;  i++)
	{
		pthread_mutex_lock(&lock1);
		pthread_mutex_lock(&lock2);
			printf("In critical section 1.\n");
			counter++;
		pthread_mutex_unlock(&lock2);
		pthread_mutex_unlock(&lock1);
	}
	return NULL;
}

void *thread2func (void *param)
{
	for (int i=0; i < 1000;  i++)
	{
		pthread_mutex_lock(&lock2);
		pthread_mutex_lock(&lock1);
			printf("In critical section 2.\n");
			counter--;
		pthread_mutex_unlock(&lock2);
		pthread_mutex_unlock(&lock1);
	}
	return NULL;
}


int main(int argc, char **argv)
{
	pthread_t threads[2];
	pthread_create(&threads[0], NULL, thread1func, NULL);
	pthread_create(&threads[1], NULL, thread2func, NULL);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	printf("\nCounter=%ld\n",counter);
	return 0;
}
