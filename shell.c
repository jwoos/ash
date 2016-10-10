#include "shell.h"

void prompt() {
	writeStdout("shell > ", 9);
}

void notAvailable() {
	writeStdout("Not supported yet\n", 18);
}

int builtIns(char* command) {
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
		notAvailable();

		matched = 1;
	} else if (sdsequal(str, quit)) {
		_exit(EXIT_SUCCESS);

		matched = 1;
	}

	sdsfreeall(sdsVector);
	return matched;
}

char* getCommand(sds commandLine) {
	char* buffer = malloc(sizeof(char) * 64);

	unsigned int position = 0;

	while (commandLine[position] != ' ' && commandLine[position] != '\0') {
		buffer[position] = commandLine[position];
		position++;
	}
	buffer[position] = '\0';

	return buffer;
}

/*
 *sds getArg(sds commandLine) {
 *    char* buffer = malloc(sizeof(char*));
 *}
 */

/*
 *char** parseCommand(char* commandLine) {
 *    char* temp;
 *
 *    int inQuotations = 0;
 *    char quotationType = '';
 *
 *    int index = 0;
 *    int commandIndex = 0;
 *
 *    int size = 1;
 *    char** commands = malloc(sizeof(char*) * size);
 *
 *    while (commandLine[index] != '\0' && commandLine != '\n') {
 *        // deal with space
 *        if (commandLine[index] == ' ' && !inQuotations) {
 *            commandIndex++;
 *            size++;
 *            commands = realloc(commands, size);
 *            commands[commandIndex = ]
 *        }
 *
 *        if (commandLine[index] == '\'') {
 *            if (!inQuotations) {
 *                quotationType = '\'';
 *                inQuotations = 1;
 *            } else {
 *                quotationType = '';
 *                inQuotations = 0;
 *                commandIndex++;
 *                size++;
 *            }
 *        } else if (commandLine[index] == '"') {
 *            quotationType = '"';
 *            inQuotations = 1;
 *        }
 *
 *        index++;
 *    }
 *}
 */
