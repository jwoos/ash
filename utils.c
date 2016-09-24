#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern const int OKAY = 0;
extern const int ERROR = 1;

void writeStdout(char message[], int bytes) {
	write(STDOUT_FILENO, message, bytes);
}

void writeStderr(char message[], int bytes) {
	write(STDERR_FILENO, message, bytes);
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

void printError(char* message, int shouldExit) {
	perror(message);
	if (shouldExit) {
		_exit(EXIT_FAILURE);
	}
}
