#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>

static int (*orig_rand)(void) = NULL;

void  __attribute__((constructor)) init (void)
{
	fprintf(stderr,"loading\n");
	//get a pointer to glib's rand function
	orig_rand = dlsym(RTLD_NEXT, "rand");
}

void  __attribute__((destructor)) cleanup (void)
{
	fprintf(stderr,"cleanup\n");
}

int rand(void)
{
	fprintf(stderr,"muhaha!\n");
	return 13;
	//return (orig_rand()%20)+1;
}
