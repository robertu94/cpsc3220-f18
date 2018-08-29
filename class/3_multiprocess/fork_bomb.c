#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
const int BIG=2<<21;
int main(int argc, char *argv[])
{
	while(true)
	{
		int ret = fork();
		char* leak = malloc(BIG);
		for(int i = 0; i<(BIG); i+=0x1000)
		{
			leak[i] = ret;
		}
	}
	return 0;
}
