#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

#include "shell.h"

int main(int argc, char* argv[]) {
	writeStdout("test\n", 5);
	writeStdout("\n", 1);

	_exit(EXIT_SUCCESS);
}

