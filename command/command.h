#ifndef ASH_COMMAND_COMMAND_H
#define ASH_COMMAND_COMMAND_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "../utils/io.h"
#include "../utils/string.h"


typedef struct command {
	char** raw;        // raw command text
	uint16_t rawSize;  // size of raw
	char* cmd;         // base command
	char** args;       // array of arguments
	uint16_t argsSize; // size of arguments
	uint8_t index;     // index relative to CommandLine
	bool pipe;         // should it pipe to next?
	bool redirect;     // should it redirect?
} Command;


Command* commandConstruct(char**, int);

void commandDeconstruct(Command*);

Command* parseCommand(char*);


#endif
