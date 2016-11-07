#include <stdlib.h>
#include <stdio.h>

#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "shell.h"

int PID;

void sigintHandler() {
	if (PID > 0) {
		kill(PID, SIGINT);
		PID = 0;
		flush();
	} else {
		flush();
		prompt();
	}
}

// TODO move to sigact
void handleSignals() {
	signal(SIGINT, *sigintHandler);
}

int main(int argc, char* argv[]) {
	handleSignals();

	while (1) {
		prompt();

		char* commandLine = readStdin();
		char** parsedCommand = parseCommand(commandLine);

		int cont = builtIns(parsedCommand[0], parsedCommand[1]);

		if (!cont && parsedCommand[0] != '\0') {
			int status;

			PID = fork();

			if (PID == 0) {
				if (execvp(parsedCommand[0], parsedCommand) == -1) {
					printError("Command failure", 1);
				}
			} else if (PID < 0) {
				printError("Error forking process", 0);
			} else {
				// wait for child process to terminate
				wait(&status);
			}
		}

		free(commandLine);
		freeArray((void**)parsedCommand, 3);
	}

	_exit(EXIT_SUCCESS);
}
