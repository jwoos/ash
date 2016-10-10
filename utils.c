#include "utils.h"

static char getCharFromStdin() {
	char buffer[1];

	int bytesRead = read(STDIN_FILENO, buffer, 1);

	if (bytesRead < 0) {
		printError("error reading - exiting", 1);
	} else if (bytesRead == 0) {
		buffer[0] = '\0';
	}

	return *buffer;
}

void flush() {
	writeStdout("\n", 1);
}

void printError(sds message, int shouldExit) {
	perror(message);

	if (shouldExit) {
		_exit(EXIT_FAILURE);
	}
}

void writeStdout(sds message, int bytes) {
	if (write(STDOUT_FILENO, message, bytes) < 0) {
		printError("error writing - exiting", 1);
	}
}

// don't use this - use printError or perror
void writeStderr(sds message, int bytes) {
	if (write(STDERR_FILENO, message, bytes) < 0) {
		printError("error writing - exiting", 1);
	}
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

		if (c == '\0' && position == 0) {
			_exit(EXIT_SUCCESS);
		} if (c == '\n') {
			buffer[position] = '\0';
			break;
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

	return buffer;
}

char** generateEmptyStringArr() {
	char** buffArr = malloc(sizeof(char*));
	buffArr[0] = malloc(sizeof(char));
	buffArr[0][0] = '\0';

	return buffArr;
}

// not binary safe
int countChars(char* buf) {
	int index = 0;

	do {
		index++;
	} while (buf[index] != '\0');

	return index;
}

/*
 * sds functions
 */

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
		sds str = vectorGet(sdsVector, i);
		sdsfree(str);
	}

	vectorDeconstruct(sdsVector);
}
