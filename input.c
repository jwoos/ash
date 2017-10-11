#include "input.h"


static char** _parseCommand(char* commandLine, int* arraySize) {
	// args will contain the actual command and the following arguments
	*arraySize = 0;

	Command* command = malloc(sizeof *command);
	char** args = malloc(sizeof *args);
	args[0] = calloc(64, sizeof *args[0]);
	command -> args = args;

	uint32_t bufferSize = 64;
	uint32_t arrayIndex = 0;
	uint32_t buffPosition = 0;
	uint32_t position = 0;

	while (commandLine[position] != '\0' && commandLine[position] != '\n') {
		if (commandLine[position] == ' ') {
			// we only want to increment arg count when space isn't found in the beginning
			if (position != 0) {
				arrayIndex++;
				buffPosition = 0;
				bufferSize = 64;
				args = realloc(args, sizeof(char*) * (arrayIndex + 1));
				args[arrayIndex] = calloc(bufferSize, sizeof(char));
			}

			// strip any extra space - we don't care
			while (commandLine[position] == ' ' && commandLine[position] != '\0' && commandLine[position] != '\n') {
				position++;
			}
			continue;
		}

		if (buffPosition == bufferSize) {
			bufferSize *= 2;
			args[arrayIndex] = realloc(args[arrayIndex], sizeof(char) * bufferSize);
		}

		args[arrayIndex][buffPosition] = commandLine[position];

		position++;
		buffPosition++;
	}

	arrayIndex++;
	args = realloc(args, sizeof(char*) * (arrayIndex + 1));
	args[arrayIndex] = NULL;

	*arraySize = arrayIndex + 1;
	return args;
}

Command* parseCommand(char* commandLine) {
	int arraySize;
	char** raw = _parseCommand(commandLine, &arraySize);

	return commandConstruct(raw, arraySize);
}

Command* commandConstruct(char** raw, int rawSize) {
	Command* command = malloc(sizeof *command);

	command -> raw = raw;
	command -> rawSize = rawSize;
	command -> cmd = raw[0];
	command -> args = raw + 1;
	command -> argsSize = rawSize - 1;

	return command;
}

void commandDeconstruct(Command* command) {
	freeArray((void**)command -> raw, command -> rawSize);
	free(command);
}

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
