#include <stdio.h>
int main()
{
	char name[10];
	if(scanf("%10s", name) > 0)
		printf("hello world %s\n", name);
	return 0;
}
