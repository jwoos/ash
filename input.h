#ifndef ASH_SHELL_H
#define ASH_SHELL_H


#include <stdbool.h>
#include <stdlib.h>


typedef struct command {
	char* command;
	char** arguments;
	bool pipe;
	bool redirect;
} Command;


#endif
