#include "command.h"


Command* commandConstruct(char* cmd, Vector* args) {
	Command* command = malloc(sizeof (*command));

	command -> cmd = cmd;
	command -> args = args;

	command -> pipe = false;
	command -> redirect = false;

	return command;
}

void commandDeconstruct(Command* command, void (*fn)(void*)) {
	free(command -> cmd);
	vectorDeconstruct(command -> args, NULL);
	free(command);
}
