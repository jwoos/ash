#include "shell.h"

void prompt() {
	writeStdout("shell > ", 9);
}

int builtIns(char* command) {
	// NEED A VECTOR TO KEEP TRACK OF SDS POINTERS
	sds str = sdsnew(command);
	sds pwd = sdsnew("pwd");

	if (sdsequal(str, sdsnew("pwd"))) {
		char cwd[512];

		// TODO check errno for array overflow
		getcwd(cwd, sizeof(cwd));

		int actualSize = countChars(cwd);

		writeStdout(cwd, actualSize);
		writeStdout("\n", 1);
		return 1;
	}

	return 0;
}
