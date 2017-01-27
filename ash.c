#include <stdlib.h>
#include <stdio.h>

#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "shell.h"

int PID;

void sigactionHandler(int sig) {
	switch (sig) {
		case SIGINT: {
			if (PID > 0) {
				kill(PID, SIGINT);
				PID = 0;
				flush();
			} else {
				flush();
				prompt();
			}
			break;
		}

		default: {
			writeStdout("Nothing matched\n", 15);
			break;
		}
	}
}

void handleSignals() {
	struct sigaction act;
	act.sa_handler = &sigactionHandler;

	if (sigaction(SIGINT, &act, NULL) != 0) {
		printError("signal handler not registered properly", 1);
	}
}

int main(int argc, char* argv[]) {
	handleSignals();

	while (1) {
		prompt();

		int arraySize = 0;
		char* commandLine = readStdin();
		char** parsedCommand = parseCommand(commandLine, &arraySize);

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
		freeArray((void**)parsedCommand, arraySize);
	}

	_exit(EXIT_SUCCESS);
}
