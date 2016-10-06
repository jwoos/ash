#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

#include "utils.h"

int main(int argc, char* argv[]) {
	while (1) {
		printf("shell > ");
		fflush(stdout);

		char* commandLine = readStdin();
		char* command = getCommand(commandLine);

		printf("commandLine: %s\n", commandLine);
		printf("command: %s\n", command);

		free(commandLine);
		free(command);
	}

	_exit(EXIT_SUCCESS);
}

