#include <iostream>
#include <dlfcn.h>


extern "C" {

static int (*orig_rand)(void) = nullptr;

void  __attribute__((constructor)) init (void)
{
	std::cerr << "loading" << std::endl;
	//reinterpet_cast is very the "C++ way" to do C like-cast, but "tries" static casting first
	if(orig_rand==nullptr)
	{
		orig_rand = reinterpret_cast<int(*)(void)>(dlsym(RTLD_NEXT, "rand"));
	}
}

void  __attribute__((destructor)) cleanup (void)
{
	std::cerr << "done" << std::endl;
}

int rand(void)
{
	std::cerr << "muhaha" << std::endl;
	return 13;
	//return (orig_rand()%20)+1;
}
}
