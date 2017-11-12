#ifndef ASH_COMMAND_LINE_H
#define ASH_COMMAND_LINE_H


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "command.h"
#include "../common.h"
#include "../data/vector.h"
#include "../utils/io.h"
#include "../utils/string.h"


typedef struct commandLine {
	char* raw;             // raw text
	Vector* commands;    // array of all the commands
} CommandLine;


CommandLine* commandLineConstruct(char*, Vector*);

void commandLineDeconstruct(CommandLine*, void (*fn)(void*));


#endif
