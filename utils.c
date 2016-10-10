#include "utils.h"

void printError(char* message, int shouldExit) {
	perror(message);

	if (shouldExit) {
		_exit(EXIT_FAILURE);
	}
}

void writeStdout(char* message, int bytes) {
	if (write(STDOUT_FILENO, message, bytes) < 0) {
		printError("error writing - exiting", 1);
	}
}

// don't use this - use printError or perror
void writeStderr(char* message, int bytes) {
	if (write(STDERR_FILENO, message, bytes) < 0) {
		printError("error writing - exiting", 1);
	}
}

// don't use malloc
char getCharFromStdin() {
	char buffer[1];
	read(STDIN_FILENO, buffer, 1);

	return *buffer;
}

char* readStdin() {
	unsigned int original = 256;
	unsigned int size = 256;
	unsigned int position = 0;
	char* buffer = malloc(sizeof(char) * size);
	char c;

	if (!buffer) {
		printError("Error allocating\n", 1);
	}

	while (1) {
		c = getCharFromStdin();

		if (c == EOF || c == '\n') {
			buffer[position] = '\0';

			return buffer;
		}

		buffer[position] = c;
		position++;

		if (position >= size) {
			size += original;
			buffer = realloc(buffer, size);
			if (!buffer) {
				printError("Error allocating\n", 1);
			}
		}
	}
}

// this does not take any arguments to the command
char* getCommand(char* commandLine) {
	char* buffer = malloc(sizeof(char) * 64);

	unsigned int position = 0;

	while (commandLine[position] != ' ' && commandLine[position] != '\0') {
		buffer[position] = commandLine[position];
		position++;
	}

	return buffer;
}

// TODO
/*
 *char** getArgs(char* commandLine) {
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

char** generateEmptyStringArr() {
	char** buffArr = malloc(sizeof(char*));
	buffArr[0] = malloc(sizeof(char));
	buffArr[0][0] = '\0';

	return buffArr;
}

/*void freeMemory(void** items, int count) {}*/

// not binary safe
int countChars(char* buf) {
	int index = 0;

	do {
		index++;
	} while (buf[index] != '\0');

	return index;
}

int sdsequal(const sds a, const sds b) {
	int sizeA = sdslen(a);
	int sizeB = sdslen(b);

	if (sizeA != sizeB) {
		return 0;
	}

	for (int i = 0; i <= sizeA; i++) {
		if (a[i] != b[i]) {
			return 0;
		}
	}

	return 1;
}

sds sdsinit(Vector* sdsVector, char* str) {
	sds sdsStr = sdsnew(str);

	vectorPush(sdsVector, sdsStr);

	return sdsStr;
}

void sdsfreeall(Vector* sdsVector) {
	int size = sdsVector -> size;

	for (int i = 0; i < size; i++) {
		sdsfree(vectorGet(sdsVector, i));
	}

	vectorDeconstruct(sdsVector);
}
