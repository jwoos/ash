#ifndef ASH_UTILS_STRING_H
#define ASH_UTILS_STRING_H


#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "../data/vector.h"


char** generateEmptyStringArr(void);

int countChars(char*);

void freeArray(void**, int);

bool strEqual(char*, char*);


#endif
