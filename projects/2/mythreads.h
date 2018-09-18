
#include <ucontext.h>

#define STACK_SIZE (16*1024)  
#define NUM_LOCKS 10 
#define CONDITIONS_PER_LOCK 10 

//the type of function used to run your threads
typedef void *(*thFuncPtr) (void *); 

extern void threadInit();
extern int threadCreate(thFuncPtr funcPtr, void *argPtr); 
extern void threadYield(); 
extern void threadJoin(int thread_id, void **result);

//exits the current thread -- closing the main thread, will terminate the program
extern void threadExit(void *result); 

extern void threadLock(int lockNum); 
extern void threadUnlock(int lockNum); 
extern void threadWait(int lockNum, int conditionNum); 
extern void threadSignal(int lockNum, int conditionNum); 

//this 
extern int interruptsAreDisabled;