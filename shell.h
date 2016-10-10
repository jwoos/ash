#ifndef ASH_SHELL_H
#define ASH_SHELL_H

#include <stdlib.h>
#include <stdio.h>

#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "utils.h"

void prompt();

void notAvailable();

int builtIns(char*);

#endif
