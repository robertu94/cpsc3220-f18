
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

ucontext_t main_context, thread_context;

int x = 0;


void thread_func(int value)
{
	printf("thread: the value is %d\n",value);
	swapcontext(&thread_context, &main_context);
	printf("thread: do something else...\n");
	swapcontext(&thread_context, &main_context);
	printf("thread: returning...aaah!\n");
}

#define STACK_SIZE 32000

int main (int argc, char **argv)
{
	char *a_new_stack = malloc(STACK_SIZE);

	//get the current context as a starting point
	//for making the new thread context.
	if (getcontext(&thread_context) == -1)
		{ perror("getcontext!"); }

	//use a different stack
	thread_context.uc_stack.ss_sp = a_new_stack;
	thread_context.uc_stack.ss_size = STACK_SIZE;
	//where to go if thread_func ever returns.
	thread_context.uc_link = &main_context; 

	makecontext(&thread_context, 
		(void (*) (void))thread_func, 1, 7);
	
	swapcontext(&main_context, &thread_context);
	printf("main: back in main!\n");
	swapcontext(&main_context, &thread_context);
	//printf("main: not quite done yet.\n");
	//swapcontext(&main_context, &thread_context);
	printf("main: returning\n");
}