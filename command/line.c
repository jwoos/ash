#include "line.h"


CommandLine* commandLineConstruct(char* raw, Vector* commands) {
	CommandLine* cl = malloc(sizeof (*cl));

	cl -> raw = raw;
	cl -> commands = commands;

	return cl;
}

void commandLineDeconstruct(CommandLine* cl, void (*fn)(void*)) {
	vectorDeconstruct(cl -> commands, fn);
	free(cl -> raw);
	free(cl);
}
