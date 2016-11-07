#ifndef ASH_UTILS_H
#define ASH_UTILS_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include "sds/sds.h"

#include "vector.h"

void flush();

void printError(sds, int);

void writeStdout(sds, int);

void writeStderr(sds, int);

char* readStdin();

char** generateEmptyStringArr();

int countChars(char*);

void freeArray(void**, int);

/*
 * sds functions
 */

int sdsequal(const sds, const sds);

sds sdsinit(Vector*, char*);

void sdsfreeall(Vector*);

#endif
