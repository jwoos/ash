#include "io.h"

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
	uint32_t original = 256;
	uint32_t size = 256;
	uint32_t position = 0;
	char* buffer = calloc(size, sizeof(*buffer));
	char c;

	if (!buffer) {
		printError("Error allocating", 1);
	}

	while (1) {
		c = getCharFromStdin();

		// ctrl-d
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
