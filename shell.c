#include <stdlib.h>
#include <stdio.h>

#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "utils.h"

int PID;

void timeoutHandler(int signum) {
	printError("Timed out, aborting...", 0);

	kill(PID, SIGKILL);
}

int main(int argc, char* argv[]) {
	int seconds = 0;
	char prompt[] = "shell > ";

	// set up alarm signal handling
	signal(SIGALRM, *timeoutHandler);

	if (argc >= 2) {
		seconds = atoi(argv[1]);
	}

	while (1) {
		writeStdout(prompt, 9);

		char* commandLine = readStdin();
		char* command = getCommand(commandLine);
		char** args = generateEmptyStringArr();
		char** env = generateEmptyStringArr();

		PID = fork();
		int status;

		// wait for child process to terminate
		wait(&status);

		// set alarm signal to send after X seconds
		if (seconds > 0) {
			alarm(seconds);
		}

		if (PID == 0) {
			if (execve(command, args, env) == -1) {
				printError("Command failure", 1);
			} else {
				// cancel alarm
				alarm(0);
			}
		} else if (PID < 0) {
			printError("Error forking process", 0);
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
