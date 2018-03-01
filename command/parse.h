#ifndef ASH_COMMAND_PARSE_H
#define ASH_COMMAND_PARSE_H


#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#include "../common.h"
#include "../utils/io.h"
#include "../utils/string.h"
#include "line.h"


CommandLine* parseCommand(char*);

void cleanUpCommand(CommandLine*);


#endif
