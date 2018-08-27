//from Dr. Sorber's OS class
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAILBOX_NUMBER 1200    //The mailbox number I want to use

struct {
   long mtype;        //message type
   char txt[30];       //body of the message
} msgp, cmbox;

//MAIN function
int main(int argc, char *argv[]) {


   //Setup local variables
   int result, length, status;
   
   //Create the Central Servers Mailbox
   int msqidS = msgget(MAILBOX_NUMBER, 0600 | IPC_CREAT);

   //Create the mailbox for this process and store it's IDs
   int msqidC = msgget((MAILBOX_NUMBER + 1), 0600 | IPC_CREAT);

   printf("S=%d, C=%d\n",msqidS, msqidC);

   //Initialize the message to be sent
   msgp.mtype = 1;
   strncpy(msgp.txt, "HELP!", sizeof(msgp.txt)-1);

   /* The length is essentially the size of 
       the structure minus sizeof(mtype) */
   length = sizeof(msgp) - sizeof(long);

   
   result = msgsnd( msqidS, &msgp, length, 0);
   printf("Sent message...\n");

   //Wait for a new message from the central server
   result = msgrcv( msqidC, &cmbox, length, 1, 0);
   printf("Recved response: type=%ld, txt=\"%s\"\n", cmbox.mtype,
      cmbox.txt);
   //Remove the mailbox
   status = msgctl(msqidC, IPC_RMID, 0);

   //Validate nothing when wrong when trying to remove mailbox
   if(status != 0){
      perror("Closing mailbox");
   }
}
