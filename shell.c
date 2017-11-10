#include "shell.h"

void prompt(void) {
	writeStdout("shell > ", 9);
}

void notAvailable(void) {
	writeStdout("Not supported yet\n", 18);
}

uint32_t builtIns(char* command, char* arg) {
	char* pwd = "pwd";
	char* cd = "cd";
	char* quit = "exit";

	int matched = 0;

	if (strEqual(command, pwd)) {
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
	} else if (strEqual(command, cd)) {
		if (chdir(arg) < 0) {
			printError("Failed to change directory", 1);
		};

		matched = 1;
	} else if (strEqual(command, quit)) {
		_exit(EXIT_SUCCESS);

		matched = 1;
	}

	return matched;
}
