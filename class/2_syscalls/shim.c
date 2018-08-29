#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

static int (*orig_rand)(void) = NULL;

void  __attribute__((constructor)) init (void)
{
	printf("loading\n");
	//get a pointer to glib's rand function
	if(orig_rand==NULL)
	{
		orig_rand = dlsym(RTLD_NEXT, "rand");
	}
}

void  __attribute__((destructor)) cleanup (void)
{
	printf("cleanup\n");
}

int rand(void)
{
	printf("muhaha!\n");
	return 13;
	//return (orig_rand()%20)+1;
}
