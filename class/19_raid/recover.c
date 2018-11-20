#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define N 4

int main(int argc, char *argv[])
{
	int fds[N] = {0};
	const char* data[N] = {NULL};
	const char* file_path = argv[1];
	struct stat file_info;

	for(int i = 0; i < N; file_path = argv[++i])
	{
		fds[i] = open(file_path, O_RDONLY);
		if(fds[i] == -1) goto done;
		fstat(fds[i], &file_info);
		data[i] = mmap(NULL, file_info.st_size, PROT_READ, MAP_SHARED, fds[i], 0);
		if(data[i] == NULL) goto done;
	}

	char* output = malloc(sizeof(char) * file_info.st_size);
	if(output != NULL)
	{

		for(int i = 0; i < file_info.st_size ; ++i)
		{
			output[i] = data[0][i] ^ data[1][i] ^ data[2][i] ^ data[3][i];
		}

		int output_fd = open(argv[5], O_WRONLY);
		if(output_fd != -1) {
			write(output_fd, output, file_info.st_size);
		}
		close(output_fd);
	}

done:
	for (int i = 0; i < N; ++i) {
		if(!fds[i])
		{
			munmap((void*)data[i], file_info.st_size);	
			close(fds[i]);
		}
	}
	return 0;
}
