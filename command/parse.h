#ifndef ASH_COMMAND_PARSE_H
#define ASH_COMMAND_PARSE_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "../utils/io.h"
#include "../utils/string.h"


char* getCommand(char*);

char** getArg(char*);


#endif
