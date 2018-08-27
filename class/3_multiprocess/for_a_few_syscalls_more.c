#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int
chose_mode()
{
	srand(time(NULL));
	return rand()%2;
}
const int add = 0;
const int sub = 1;

void
child()
{
  int mode = chose_mode();
  if (mode == add) {
    setenv("TASK_ID", "add", true);
  } else if (mode == sub) {
    setenv("TASK_ID", "sub", true);
  }
  char* const argv[] = { "child", "15", "1", "2", "3", "4", "5" , NULL};
	printf("calling child\n");
	execvpe("./child", argv, environ);

	perror("failed to_exec");
	exit(1);
}

int
main(int argc, char* argv[])
{
  pid_t pid = fork();
  switch (pid) {
    case 0:
      child();
      break;
    case -1:
      perror("failed to fork");
      exit(1);
    default:
      /*intentional no-op to silence compiler*/
      break;
  }
	wait(NULL);


  return 0;
}
// vim: foldmethod=marker :
