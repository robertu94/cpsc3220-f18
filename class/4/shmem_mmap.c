// modified from an example used in Dr. Sorber's OS class
// specifically prefer removed non-standard error handling functions
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int
main(void)
{
  const char str1[] = "old text";
  const char str2[] = "some new text";

  int parpid = getpid(), childpid;
  char* sharedblock;
  int unshared = 12;

  // map a block of 4K that will be shared between child and
  // parent after fork()
  sharedblock = (char*)mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                            MAP_ANON | MAP_SHARED, -1, 0);

  if (sharedblock == MAP_FAILED) {
    perror("mmap error");
    exit(EXIT_FAILURE);
  }

  strcpy(sharedblock, str1);

  printf("PID %d:\tshared= \"%s\" unshared=%d (before fork)\n", parpid,
         sharedblock, unshared);
  switch ((childpid = fork())) {
    case -1:
      perror("mmap error");
      exit(EXIT_FAILURE);
      /* NOTREACHED */

    case 0: // child process
      childpid = getpid();
      printf("PID %d:\tshared= \"%s\" unshared=%d (child)\n", childpid,
             sharedblock, unshared);
      sleep(2);
      printf("PID %d:\tshared= \"%s\" unshared=%d (child, after sleep)\n",
             childpid, sharedblock, unshared);
      strcpy(sharedblock, "childish text!!! :)");
      unshared = 77777; // this one wont show up in the parent

      // don't want the memory anymore.
      munmap(sharedblock, 4096);

      // if you write to sharedblock at this point, you will probably
      // seg fault
      return 0;
  }

  // parent process
  sleep(1);
  printf("PID %d:\tshared= \"%s\" unshared=%d (parent, before strcpy)\n",
         parpid, sharedblock, unshared);

  strcpy(sharedblock, str2);
  unshared = 145;

  printf("PID %d:\tshared= \"%s\" unshared=%d (parent, after strcpy)\n", parpid,
         sharedblock, unshared);

  waitpid(childpid, NULL, 0);
  printf("PID %d:\tshared= \"%s\" unshared=%d (parent, after waitpid)\n",
         parpid, sharedblock, unshared);

  munmap(sharedblock, 4096);

  return 0;
}
