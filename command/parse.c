#include "parse.h"


char* getCommand(char* commandLine) {
	char* buffer = malloc(sizeof(char) * 64);

	int position = 0;

	while (commandLine[position] != ' ' && commandLine[position] != '\0') {
		buffer[position] = commandLine[position];
		position++;
	}
	buffer[position] = '\0';

	return buffer;
}

char** getArg(char* commandLine) {
	char** args = malloc(sizeof(char*));
	args[0] = malloc(sizeof(char) * 64);
	char* buffer = args[0];

	int position = 0;

	while (commandLine[position] != ' ' && commandLine[position] != '\0') {
		position++;
	}
	position++;

	int buffPosition = 0;

	while (commandLine[position] != ' ' && commandLine[position] != '\0') {
		buffer[buffPosition] = commandLine[position];
		buffPosition++;
		position++;
	}
	buffer[buffPosition] = '\0';

	return args;
}
