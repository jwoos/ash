#ifndef ASH_COMMAND_H
#define ASH_COMMAND_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../utils/io.h"
#include "../utils/string.h"


typedef struct Command {
	char* raw;
	char* base;
	Vector* args;
} Command;


Command* commandConstruct(const char*);

void commandDeconstruct(Command*, void (*fn)(void*));


#endif
