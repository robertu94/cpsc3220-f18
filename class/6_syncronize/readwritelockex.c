//this file comes from Dr. Sorber's OS class
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

unsigned long counter = 0;

pthread_rwlock_t my_reader_writer_lock;


void *writer_thread_func (void *param)
{
	while (1) {
		sleep(4);
		//every 5 seconds update the value
		pthread_rwlock_wrlock(&my_reader_writer_lock);
			printf("Writing!\n");
			sleep(3);
			counter++;
			printf("Writing done!\n");
		pthread_rwlock_unlock(&my_reader_writer_lock);
	}
	return NULL;
}

void *reader_thread_func (void *param)
{
	//I know, I know, I just cast a pointer
	//to an int.
	long num = (long) param; 
	while (1)
	{
		pthread_rwlock_rdlock(&my_reader_writer_lock);
			printf("thread #%ld: read %lu\n",num, counter);
		pthread_rwlock_unlock(&my_reader_writer_lock);
		sleep(rand() % 3);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t readers[NUM_THREADS];
	pthread_t writer;

	//initialize reader-writer lock with default attributes
	pthread_rwlock_init(&my_reader_writer_lock, NULL);

	for (long i=0; i < NUM_THREADS; i++)
	{
		pthread_create(&readers[i], NULL, 
			reader_thread_func, (void*)i);		
	}


	pthread_create(&writer, NULL, 
		writer_thread_func, NULL);

	pthread_join(writer,NULL); //basically wait forever.
	return 0;
}
