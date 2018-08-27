#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
int main(int argc, char *argv[])
{
	while(true)
	{
		fork();
		char* leak = malloc(2<<8);
		leak[0] = 'a';
	}
	return 0;
}
