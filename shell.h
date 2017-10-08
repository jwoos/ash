#ifndef ASH_SHELL_H
#define ASH_SHELL_H


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

#include "utils.h"
#include "input.h"


void prompt();

void notAvailable();

uint32_t builtIns(char*, char*);


#endif
