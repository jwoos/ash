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
		char* command = getCommand(commandLine);
		char** arg = getArg(commandLine);
		char** args = generateEmptyStringArr();
		char** env = generateEmptyStringArr();

		int cont = builtIns(command, arg[0]);

		if (!cont && command[0] != '\0') {
			int status;

			PID = fork();

			if (PID == 0) {
				if (execve(command, args, env) == -1) {
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
		free(command);
		free(arg);
		free(args[0]);
		free(args);
		free(env[0]);
		free(env);
	}

	_exit(EXIT_SUCCESS);
}
