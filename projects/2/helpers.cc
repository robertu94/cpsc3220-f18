#include <pthread.h>
#include <cstdio>

/*
 * An example of how a helper function can help you find a return value
 */

int b = 4;

struct args {
	int* a;
	int* (*my_addr)(int *);
};

void* mythread(void* data)
{
	struct args* arg = (struct args*)data;
	int* ret = arg->my_addr(arg->a);

	pthread_exit(ret);
}

int * add(int* a)
{
	pthread_exit(a);
	*a+= 3;
	return a;
}

int main(int argc, char *argv[])
{
	pthread_t thread;
	struct args args;
	int* c;
	args.a = &b;
	args.my_addr = add;
	pthread_create(&thread, NULL, mythread, (void*)&args);
	pthread_join(thread, (void**)&c);

	printf("%d\n",*c);
	return 0;
}
