#ifndef ASH_UTILS_IO_H
#define ASH_UTILS_IO_H


#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "../data/vector.h"


void flush(void);

void printError(char*, int);

void writeStdout(char*, int);

void writeStderr(char*, int);

char* readStdin(void);


#endif
