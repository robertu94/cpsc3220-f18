//this file comes from Dr. Sorber's OS class
#include	<time.h>
#include 	<pthread.h>
#include 	<assert.h>
#include    <stdlib.h>
#include    <sys/stat.h>
#include    <unistd.h>
#include    <stdio.h>
#include 	<semaphore.h>
#include 	<stdint.h>

#define NUM_THREADS 3
#define NUM_BUFFERS 5 
#define ITERATIONS 10

sem_t empty_semaphore;
sem_t full_semaphore;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int front = 0;
int back = 0;
char *buffer[NUM_BUFFERS];

void * consumer_func (void *arg)
{
	int id = (int) arg;

	while (1)
	{

		printf("[%d] waiting\n",id);

		//wait for a buffer to be full
		sem_wait(&full_semaphore);

		char *thebuf;
		int oldback;
		
		pthread_mutex_lock(&mutex);
		thebuf = buffer[back];
		buffer[back] = NULL;
		oldback = back;
		back = (back + 1) % NUM_BUFFERS;
		pthread_mutex_unlock(&mutex);

		printf("[%d] consume @(%d) -- %s\n",id, oldback, thebuf);
		free(thebuf);
		
		
	
		//signal producer that there is now room
		sem_post(&empty_semaphore);
	}
	return NULL;
}

void * producer_func (void *arg)
{
	for (int i=0; i < ITERATIONS; i++)
	{
		//wait for a buffer to be empty
		sem_wait(&empty_semaphore);

		pthread_mutex_lock(&mutex);
		//produce another message
		buffer[front] = malloc(1024);
		sprintf(buffer[front],"message %d",i);
		printf("producing @(%d) -- %s\n", front, buffer[front]);
		front = (front + 1) % NUM_BUFFERS;
		pthread_mutex_unlock(&mutex);
		

		sem_post(&full_semaphore);
	}
	return NULL;
}

int main()
{
	//initialize my_semaphore, 
	//	no sharing, 
	//	initial value of SEM_INIT_VALUE
	sem_init(&empty_semaphore, 0, NUM_BUFFERS);
	sem_init(&full_semaphore, 0, 0);

	pthread_t consumers[NUM_THREADS];
	pthread_t producer;

	for (long i=0; i < NUM_THREADS; i++)
	{
		pthread_create(&consumers[i], NULL, 
			consumer_func, (void*)i);
	}

	pthread_create(&producer, NULL, producer_func, NULL);
	//wait for completion
	for (int i=0; i < NUM_THREADS; i++)
	{
		pthread_join(consumers[i], NULL);
	}	

	
}
