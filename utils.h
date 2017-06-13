#ifndef ASH_UTILS_H
#define ASH_UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "vector.h"

void flush();

void printError(char*, int);

void writeStdout(char*, int);

void writeStderr(char*, int);

char* readStdin();

char** generateEmptyStringArr();

int countChars(char*);

void freeArray(void**, int);

bool strEqual(char*, char*);

#endif
