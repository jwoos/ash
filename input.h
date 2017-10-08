#ifndef ASH_INPUT_H
#define ASH_INPUT_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.h"


typedef struct command {
	char** raw;
	int rawSize;
	char* cmd;
	char** args;
	int argsSize;
	bool pipe;
	bool redirect;
} Command;

Command* commandConstruct(char**, int);

void commandDeconstruct(Command*);

char* getCommand(char*);

Command* parseCommand(char*);

char** getArg(char*);

char** _parseCommand(char*, int*);


#endif
