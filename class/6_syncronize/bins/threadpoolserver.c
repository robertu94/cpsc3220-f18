#include	"common.h"
#include	<time.h>
#include 	<pthread.h>
#include 	<assert.h>

//how many threads to keep "at the ready"
#define POOL_SIZE 10

//	When using a thread pool, you need a queue or similar datastructure that will
//	act as a "work queue". This is where idle threads go to get work to do.
typedef struct task {
	int connfd;
	struct task *next;
} task;

task *job_queue_head = NULL;
task *job_queue_tail = NULL;
pthread_cond_t condQueueReady = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qMutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_connection(int connection_socket);
void *thread_pool_func(void *tid);
void enqueue_connection(int connfd);
int dequeue_connection();


int main(int argc, char **argv)
{
	int					listenfd;
	struct sockaddr_in	servaddr;
	pthread_t *pool = calloc(sizeof(pthread_t),POOL_SIZE);
	

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
		err_n_die("socket error.");

	int reuse = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERVER_PORT);	/* server port */

	if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
		err_n_die("bind error.");

	if ((listen(listenfd, LISTENQ)) < 0)
		err_n_die("listen error.");
	

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

	for ( ; ; ) 
	{
		int connfd;
	
		//accept blocks until an incoming connection arrives
		//it returns a "file descriptor" to the connection
		printf("Main Thread: waiting for a connection...\n");
		fflush(stdout);
		connfd = Accept(listenfd, (SA *) NULL, NULL);
		enqueue_connection(connfd);
		
	}
}

void *thread_pool_func(void *tid)
{
	int thread_num = *((int*)tid);
	
	printf("Thread %d: started [%d]\n",thread_num,(int)pthread_self());
	
	while(1)
	{
		int connfd = dequeue_connection();
		
		printf("Thread #%d: got a connection...\n",thread_num);
		handle_connection(connfd);
		printf("Thread #%d: done, reporting for duty...\n",thread_num);
		
	}
}

void *handle_connection(int connection_socket)
{
	char				buff[MAXLINE+1];
	char				recvline[MAXLINE+1];
	time_t				ticks;
	int 				n;
	
	
	//Now read the client's message.
	while ( (n = read(connection_socket, recvline, MAXLINE)) > 0) 
	{
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_n_die("fputs error");
	
		//detect the end of the message.
		if (recvline[n-1] == '\n')
		{
			break;
		}
	}
	if (n < 0)
	{
		perror("read error");
		//err_n_die("read error");
	} else {
		
		//now send a response.
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "Thanks. Recved at (%.24s)\r\n", ctime(&ticks));

		//note: normally, you may want to check the results from write and close
		//in case errors occur. For now, I'm ignoring them.
		write(connection_socket, buff, strlen(buff));
	}
	close(connection_socket);
	return NULL;
}

void enqueue_connection(int connfd)
{
	task *ptask = (task*)malloc(sizeof(task));
	
	ptask->connfd = connfd;
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
	pthread_cond_signal(&condQueueReady);
	pthread_mutex_unlock(&qMutex);
	
}

//blocks, and suspends the thread until there's a job, then returns it.
int dequeue_connection()
{
	int return_value;
	task *ptemp;
	
	pthread_mutex_lock(&qMutex);
		assert(job_queue_tail != NULL || job_queue_head == NULL); //paranoid consistency check
		
		while (job_queue_head == NULL)
		{
			//pthread_mutex_unlock(&qMutex);
			//sleep(1);
			pthread_cond_wait(&condQueueReady, &qMutex);
			//pthread_mutex_lock(&qMutex);
		}
		return_value = job_queue_head->connfd;
		ptemp = job_queue_head;
		job_queue_head = job_queue_head->next;
		if (job_queue_tail == ptemp) job_queue_tail = NULL;
		
		assert(job_queue_tail != NULL || job_queue_head == NULL); //paranoid consistency check
	pthread_mutex_unlock(&qMutex);
	
	assert (ptemp != NULL);
	free(ptemp);
	return return_value;
}



