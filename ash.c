#include <stdlib.h>
#include <stdio.h>

#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "shell.h"

int main(int argc, char* argv[]) {
	int PID;

	while (1) {
		prompt();

		char* commandLine = readStdin();
		// parse whole input for command
		char* command = getCommand(commandLine);
		char** args = generateEmptyStringArr();
		char** env = generateEmptyStringArr();

		int cont = builtIns(command);

		if (cont) {
			continue;
		}

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

		free(command);
		free(commandLine);
		free(args[0]);
		free(args);
		free(env[0]);
		free(env);
	}

	_exit(EXIT_SUCCESS);
}
