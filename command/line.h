#ifndef ASH_COMMAND_LINE_H
#define ASH_COMMAND_LINE_H


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "command.h"
#include "../utils/io.h"
#include "../utils/string.h"


typedef struct commandLine {
	char** raw;            // raw text
	uint16_t rawSize;      // size of raw
	Command** commands;    // array of all the commands
	uint16_t commandsSize; // size of commands
} CommandLine;

CommandLine* commandLineConstruct(char* commandLine, int arraySize);


#endif
