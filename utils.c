#include <errno.h>

#include "utils.h"

static char getCharFromStdin(void) {
	char buffer[1];

	int bytesRead = read(STDIN_FILENO, buffer, 1);

	if (bytesRead < 0) {
		if (errno != EINTR) {
			printError("error reading - exiting", 1);
		} else {
			buffer[0] = ' ';
		}
	} else if (bytesRead == 0) {
		buffer[0] = '\0';
	}

	return *buffer;
}

void flush(void) {
	writeStdout("\n", 1);
}

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

char* readStdin(void) {
	unsigned int original = 256;
	unsigned int size = 256;
	unsigned int position = 0;
	char* buffer = calloc(size, sizeof(char));
	char c;

	if (!buffer) {
		printError("Error allocating", 1);
	}

	while (1) {
		c = getCharFromStdin();

		if (c == '\0' && position == 0) {
			_exit(EXIT_SUCCESS);
		} else if (c == '\n') {
			buffer[position] = '\0';
			break;
		}

		buffer[position] = c;
		position++;

		if (position >= size) {
			size += original;
			buffer = realloc(buffer, size);
			if (!buffer) {
				printError("Error allocating", 1);
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

void freeArray(void** arr, int size) {
	for (int i = 0; i < size; i++) {
		free(arr[i]);
	}

	free(arr);
}

bool strEqual(char* a, char* b) {
	int aLength = strlen(a);
	int bLength = strlen(b);

	if (aLength != bLength) {
		return false;
	}

	for (int i = 0; i < aLength; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}

	return true;
}
