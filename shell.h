#ifndef ASH_SHELL_H
#define ASH_SHELL_H


#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils/io.h"
#include "utils/string.h"
#include "command/parse.h"


void prompt(void);

void notAvailable(void);

bool builtIns(const char*, const char*);


#endif
