//this file comes from Dr. Sorber's OS class
#include	<time.h>
#include 	<pthread.h>
#include 	<assert.h>
#include    <stdlib.h>
#include    <sys/stat.h>
#include    <unistd.h>
#include    <stdio.h>

//#define BUSY

//how many threads to keep "at the ready"
#define POOL_SIZE 10

//	When using a thread pool, you need a queue or similar datastructure that will
//	act as a "work queue". This is where idle threads go to get work to do.
typedef struct task {
	char *filename;
	struct task *next;
} task;

task *job_queue_head = NULL;
task *job_queue_tail = NULL;

pthread_cond_t condQueueReady = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qMutex = PTHREAD_MUTEX_INITIALIZER;

void getfileinfo(int tid, char*filename);
void *thread_pool_func(void *tid);
void enqueue_task(char *fname);
char * dequeue_task();



int main(int argc, char **argv)
{
	
	pthread_t *pool = calloc(sizeof(pthread_t),POOL_SIZE);
	
	//Create thread pool
	for(int i=0; i < POOL_SIZE; i++)
	{
		int *tid = malloc(sizeof(int));
		*tid = i;
		if (pthread_create(&(pool[i]), NULL, thread_pool_func, tid) != 0)
		{
			fprintf(stderr, "Could not create thread #%d.\n",i);
			exit(-1);
		}
	}
	printf("created thread pool...");


	printf("Main Thread: about to start giving the thread pool tasks to work on...\n");
	fflush(stdout);
	
    while (1)
    {
        enqueue_task("./bins/interactivebank.c");
        enqueue_task("./bins/Makefile");
        enqueue_task("./bins/pthreadex.c");
        enqueue_task("./conditionex.c");
        sleep(1);
    }
    
    
}

void *thread_pool_func(void *tid)
{
	int thread_num = *((int*)tid);
	
	printf("Thread %d: started [%d]\n",thread_num,(int)pthread_self());
	
    //forever, get tasks and execute them.
	while(1)
	{
		char *fname = dequeue_task();
		
		getfileinfo(thread_num, fname);
		
	}
}

void getfileinfo(int thread_id, char *filename)
{
	struct stat finfo;
    
    if (stat(filename, &finfo) != 0)
    {
        printf("%d: couldn't stat \"%s\"", thread_id, filename);
    } else {
        printf("%d: %s\n"
            "\tsize: %ld bytes\n"
            "\tblocks: %ld\n"
            "\tuser-id: %d\n\n", thread_id, filename, finfo.st_size, finfo.st_blocks, finfo.st_uid);
    }
}

void enqueue_task(char *fname)
{
	task *ptask = (task*)malloc(sizeof(task));
	
	ptask->filename = fname;
	ptask->next = NULL;
	
	pthread_mutex_lock(&qMutex);
		assert(job_queue_tail != NULL || job_queue_head == NULL); //paranoid consistency check

		if (job_queue_head == NULL)
		{
			job_queue_head = ptask;
			job_queue_tail = ptask;
		} else {
			job_queue_tail->next = ptask;
			job_queue_tail = ptask;
		}
		
		assert(job_queue_tail != NULL || job_queue_head == NULL); //paranoid consistency check
#ifndef BUSY
        pthread_cond_signal(&condQueueReady);
#endif
	pthread_mutex_unlock(&qMutex);
	
}

//blocks, and suspends the thread until there's a file to stat, then returns it.
char* dequeue_task()
{
	char* return_value;
	task *ptemp;
	
	pthread_mutex_lock(&qMutex);
		assert(job_queue_tail != NULL || job_queue_head == NULL); //paranoid consistency check
		
		while (job_queue_head == NULL)
		{
#ifdef BUSY
            //the busy way -- release the lock so that another thread
            //                else can put something on the queue
			pthread_mutex_unlock(&qMutex);
            pthread_mutex_lock(&qMutex);
#else            
            //or a more elegant and efficient way
            pthread_cond_wait(&condQueueReady, &qMutex);
#endif
		}
		return_value = job_queue_head->filename;
		ptemp = job_queue_head;
		job_queue_head = job_queue_head->next;
		if (job_queue_tail == ptemp) job_queue_tail = NULL;
		
		assert(job_queue_tail != NULL || job_queue_head == NULL); //paranoid consistency check
	pthread_mutex_unlock(&qMutex);
	
	assert (ptemp != NULL);
	free(ptemp);
	return return_value;
}
