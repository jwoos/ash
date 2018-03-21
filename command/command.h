#ifndef ASH_COMMAND_COMMAND_H
#define ASH_COMMAND_COMMAND_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "../utils/io.h"
#include "../utils/string.h"


typedef struct Command {
	char* cmd;         // base command
	Vector* args;      // arguments
	bool pipe;         // should it pipe to next?
	bool redirect;     // should it redirect?
} Command;


Command* commandConstruct(char*, Vector*);

void commandDeconstruct(Command*, void (*fn)(void*));


#endif
