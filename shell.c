#include "sds/sds.h"
#include "shell.h"

void prompt() {
	writeStdout("shell > ", 9);
}

int builtIns(char* command) {
	// need a checker
	if (command == "pwd") {
		int size = 1024;
		char cwd[size];

		// TODO check errno for array overflow
		if (getcwd(cwd, size) == NULL) {
			printError("Failed to get current directory - exiting", 1);
		}

		int actualSize = countChars(cwd);

		writeStdout(cwd, actualSize);
		return 1;
	}

	return 0;
}
