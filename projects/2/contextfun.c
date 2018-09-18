
#include <ucontext.h>
#include <stdio.h>

ucontext_t first_context, second_context;

int x = 0;


int foo(int value)
{
	printf("foo(%d) x = %d\n",value,x);

	if (x <= 1)
	{
		x++;
		//save current context to second_context,
		//switch to first_context
		printf("pre swap (v = %d, x == %d)\n",value, x);
		swapcontext(&second_context, &first_context);
		printf("Came back (v = %d, x == %d)\n",value, x);
	}

	return x;
}


int main (int argc, char **argv)
{
	int v = 0;
	//save the context
	//we'll jump back here later.
	getcontext(&first_context);

	v++;
	int r = foo(v);

	printf("done. (r = %d).\n", r);
	setcontext(&second_context);
	printf("The end (r = %d).\n",r);
}