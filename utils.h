#ifndef ASH_UTILS_H
#define ASH_UTILS_H

#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>

void writeStdout(char [], int);

void writeStderr(char [], int);

char* readStdin();

char getCharFromStdin();

void printError(char*, int);

char* getCommand(char*);

//char** getArgs(char*);

//char** parseCommand(char*);

char** generateEmptyStringArr();

//void freeMemory(void**, int);

int countChars(char* buf);

#endif
