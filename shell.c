#include "shell.h"

void prompt() {
	writeStdout("shell > ", 9);
}

void notAvailable() {
	writeStdout("Not supported yet\n", 18);
}

int builtIns(char* command, char* arg) {
	Vector* sdsVector = vectorInitialize();

	sds str = sdsinit(sdsVector, command);
	sds pwd = sdsinit(sdsVector, "pwd");
	sds cd = sdsinit(sdsVector, "cd");
	sds quit = sdsinit(sdsVector, "exit");

	int matched = 0;

	if (sdsequal(str, pwd)) {
		char cwd[512];
		char* ptr;

		getcwd(cwd, sizeof(cwd));
		ptr = cwd;

		if (errno == ERANGE) {
			char biggerCwd[1024];
			getcwd(biggerCwd, sizeof(biggerCwd));

			ptr = biggerCwd;
		}

		int actualSize = countChars(ptr);

		writeStdout(ptr, actualSize);
		writeStdout("\n", 1);

		matched = 1;
	} else if (sdsequal(str, cd)) {
		if (chdir(arg) < 0) {
			printError("Failed to change directory", 1);
		};

		matched = 1;
	} else if (sdsequal(str, quit)) {
		_exit(EXIT_SUCCESS);

		matched = 1;
	}

	sdsfreeall(sdsVector);
	return matched;
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

char** parseCommand(char* commandLine, int* arraySize) {
	// args will contain the actual command and the following arguments
	char** args = malloc(sizeof(char*));
	args[0] = calloc(64, sizeof(char));

	int bufferSize = 64;
	int arrayIndex = 0;
	int buffPosition = 0;
	int position = 0;

	while (commandLine[position] != '\0' && commandLine[position] != '\n') {
		if (commandLine[position] == ' ') {
			if (commandLine[position + 1] == ' ' || !commandLine[position]) {
				break;
			}

			arrayIndex++;
			buffPosition = 0;
			bufferSize = 64;
			args = realloc(args, sizeof(char*) * (arrayIndex + 1));
			args[arrayIndex] = calloc(bufferSize, sizeof(char));
			position++;
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
