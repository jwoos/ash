#include "command.h"


Command* commandConstruct(const char* input) {
	Command* command = malloc(sizeof (*command));
	int inputSize = strlen(input);

	// copy over raw string
	command -> raw = malloc(sizeof (char) * inputSize);
	strncpy(command -> raw, input, inputSize);

	command -> base = NULL;
	command -> args = vectorConstruct(2);

	return command;
}

void commandDeconstruct(Command* command, void (*fn)(void*)) {
	free(command -> input);
	vectorDeconstruct(command -> args, NULL);
	free(command);
}
