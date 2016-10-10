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

		// TODO check errno for array overflow
		getcwd(cwd, sizeof(cwd));

		int actualSize = countChars(cwd);

		writeStdout(cwd, actualSize);
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
