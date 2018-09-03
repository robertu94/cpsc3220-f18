#include <string.h>
#include "bank.h"

static int current_balance;


int bank_init(int initial_balance)
{
	if (initial_balance < 0) return 0;
	current_balance = initial_balance;
	return 1;
}

//performs a command on the bank account.
//for recognized commands, the function 
//    returns the current balance, whether or not the requested
//    command was performed.
//returns -1 if the command wasn't recognized.
int bank_do_command(char *command, int value)
{
	if (strcmp(command, "balance") == 0) return current_balance;
	if (strcmp(command, "deposit") == 0)
	{
		if (value < 0) return -1; //generic error return
		current_balance += value;
		return current_balance;
	}
	if (strcmp(command, "withdraw") == 0)
	{
		if (value < 0 || current_balance < value) return current_balance; 
		current_balance -= value;
		return current_balance;
	}
	//I don't recognize this command
	return -1;
}
