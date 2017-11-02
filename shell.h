#ifndef ASH_SHELL_H
#define ASH_SHELL_H


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include "utils/io.h"
#include "utils/string.h"
#include "command/line.h"
#include "command/command.h"
#include "command/parse.h"


void prompt(void);

void notAvailable(void);

uint32_t builtIns(char*, char*);


#endif
