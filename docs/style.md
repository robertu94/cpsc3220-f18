I wanted to provide some written documentation of what constitutes good style for purposes of this class.

# Consistent Indentation and Naming

Your code should have consistent indentation and naming.  I don't care which scheme you adopt (linux, google, llvm, bsd, knr, etc...), but please be consistent.

bad:

```c
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
int condition = atoi(argv[1]);
if(condition)
printf("adsf\n");
else
printf("fdas\n");
}

void also_bad()
{
                printf("please ");
    printf("be ");
            printf("consistent!\n");
}
```

good:

```
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	int condition = atoi(argv[1]);
	if(condition) {
		printf("adsf\n");
	} else {
		printf("fdas\n");
	}
}
```

# No Magic Numbers

Your code should not have any magic numbers. In the follow code 548 is a magic number:

bad:

```c
//this is a snippet form a larger file
extern int* syscalls;
void write_systemcalls(FILE* output)
{
	for (int i = 0; i < 548; ++i) {
		fprintf(output, "%d\t%d\n", i, syscalls[i]);
	}
}
```

good:

```c
//this is a snippet form a larger file
#define NUM_SYSCALLS 548
extern int* syscalls;
void write_systemcalls(FILE* output)
{
	for (int i = 0; i < NUM_SYSCALLS; ++i) {
		fprintf(output, "%d\t%d\n", i, syscalls[i]);
	}
}
```

# Good Comments

Your code should have documenting comments for each key function that describe the pre-conditions, post-conditions and any key invariants.  A key function is one with 3 or more lines.  You should omit obvious comments.

The next sample is bad because it contains an obvious comment and has no documentation of functions preconditions and postconditions that are expected.

bad:

```c
//this is a snippet form a larger file

void write_systemcalls(FILE* output)
{
	for (int i = 0; i < 548; ++i) {
		//prints to the output file
		fprintf(output, "%d\t%d\n", i, syscalls[i]);
	}
}
```


good:


```c
//this is a snippet form a larger file

/*
 * Writes the list of systemcalls to the provided file.
 * pre-condition: file is not nullptr, syscalls contains a count of systemcalls
 * post-condition: file is either valid or -1 is returned and `output` is in an undefined state
 */
int write_systemcalls(FILE* output)
{
	int err;
	for (int i = 0; i < 548; ++i) {
		err = fprintf(output, "%d\t%d\n", i, syscalls[i]);
		if(err < 0)
		{
			return err;
		}
	}
}
```

