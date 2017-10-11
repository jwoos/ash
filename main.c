#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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

void handleSignals(void) {
	struct sigaction act;
	act.sa_handler = &sigactionHandler;
	// don't reset the handler
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) < 0) {
		printError("signal handler not registered properly", 1);
	}
}

int main(int argc, char* argv[]) {
	handleSignals();

	Command* cmd;
	char* commandLine;
	while (1) {
		prompt();

		commandLine = readStdin();
		cmd = parseCommand(commandLine);

		uint32_t cont = builtIns(cmd -> cmd, cmd -> args[0]);
		if (!cont && cmd -> cmd[0] != '\0') {
			int status;

			PID = fork();

			if (PID == 0) {
				if (execvp(cmd -> cmd, cmd -> raw) == -1) {
					printError("Command failure", 1);
				}
			} else if (PID < 0) {
				printError("Error forking process", 0);
			} else {
				// wait for child process to terminate
				wait(&status);
			}
		}

		commandDeconstruct(cmd);
	}

	/*_exit(EXIT_SUCCESS);*/
	return 0;
}
