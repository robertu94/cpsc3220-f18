//from Dr. Sorber's OS class
#define _GNU_SOURCE

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


   printf("\nStarting Server...\n");

   //Set up local variables
   int result,length,status;             //counter for loops
   
   //Create the Mailbox
   int msqidS = msgget(MAILBOX_NUMBER, 0600 | IPC_CREAT);

   //Create a mailbox for the other process
   int msqidC = msgget((MAILBOX_NUMBER + 1), 0600 | IPC_CREAT);
   

   //Initialize the message to be sent
   msgp.mtype = 1;
   strncpy(msgp.txt, "Hello", sizeof(msgp.txt)-1);
   
   /* The length is essentially the size 
       of the structure minus sizeof(mtype) */
   length = sizeof(msgp)-sizeof(long);

   //wait for a message
   result = msgrcv(msqidS, &cmbox, length, 1, 0);
   if (result < 0){
      perror("msgrcv");
   }

   printf("Received message (type=%ld, txt=\"%s\") => %d",
      cmbox.mtype,cmbox.txt,result);

   //send response.
   msgsnd(msqidC, &msgp, length, 0);

   printf("\nShutting down Server...\n");

   //Remove my own mailbox
   status = msgctl(msqidS, IPC_RMID, 0);

   //Validate nothing when wrong when trying to remove mailbox
   if(status != 0){
      perror("closing.");
      printf("\nERROR closing mailbox\n");
   }
}
