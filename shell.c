#include "shell.h"


void prompt(void) {
	writeStdout("shell > ", 9);
}

void notAvailable(void) {
	writeStdout("Not supported yet\n", 18);
}

bool builtIns(const char* command, const char* arg) {
	bool matched = false;

	if (!strncmp(command, "pwd", 3)) {
		char cwd[512];
		char* ptr;

		getcwd(cwd, sizeof(cwd));
		ptr = cwd;

		while (errno == ERANGE) {
			errno = 0;

			char biggerCwd[1024];
			getcwd(biggerCwd, sizeof(biggerCwd));

			ptr = biggerCwd;
		}

		int actualSize = countChars(ptr);

		writeStdout(ptr, actualSize);
		writeStdout("\n", 1);

		matched = true;
	} else if (!strncmp(command, "cd", 2)) {
		if (chdir(arg) < 0) {
			printError("Failed to change directory", 1);
		};

		matched = true;
	} else if (!strncmp(command, "exit", 4)) {
		exit(EXIT_SUCCESS);

		matched = true;
	}

	return matched;
}
