//Taken from Dr. Sorber's OS class
//this example shows how to use the ptrace API to 


#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>



int main(int argc, char **argv) {

    
    pid_t child = fork();
    if (child == 0) {

        //do something childish
        ptrace(PTRACE_TRACEME);

        printf("Hello. I'm the child process.\n");
        
        //stop myself --allow the parent to get ready to trace me
        kill(getpid(), SIGSTOP);

        //do something that will result in a system call
        child = getpid();
        printf("Hello. I'm the child process.\n");

        //if I wanted to trace another program, this would be a good place
        //for a call to exec*

    } else {
        int status,syscall_num;
        //I'm the parent...keep tabs on that child process

        //wait for the child to stop itself
        waitpid(child, &status, 0);

        //this option makes it easier to distinguish normal traps from
        //system calls
        ptrace(PTRACE_SETOPTIONS, child, 0, 
                PTRACE_O_TRACESYSGOOD);

        do{
            //I want to wait for a system call
            ptrace(PTRACE_SYSCALL, child, 0, 0);
            
            //actually wait for child status to change
            waitpid(child, &status, 0);

            if (WIFEXITED(status)) {
                //the child exited...let's exit too
                exit(1);
            }

            //wait until the process is stopped or bit 7 is set in 
            //the status (see man page comment on 
            //PTRACE_O_TRACESYSGOOD)
        } while (!(WIFSTOPPED(status) && 
            WSTOPSIG(status) & 0x80));

        //read out the saved value of the RAX register, 
        //which contains the system call number
        //For 32-bit machines, you would use EAX.
        syscall_num = ptrace(PTRACE_PEEKUSER, 
            child, sizeof(long)*ORIG_RAX, NULL);
        printf("My child called system call #%d.\n",syscall_num);

        //for this example, I only want the first
        //system call. So...
        //let the child run to completion
        ptrace(PTRACE_CONT, child, NULL, NULL);
        waitpid(child, NULL, 0);

    
    }
}


