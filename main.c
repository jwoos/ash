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

	CommandLine* cl;
	char* input;
	while (1) {
		prompt();

		input = readStdin();
		cl = parseCommand(input);
		Vector* commands = cl -> commands;

		for (uint32_t i = 0; i < commands -> size; i++) {
			Command* cmd = vectorGet(commands, i);
			char* base = cmd -> cmd;
			Vector* args = cmd -> args;

			uint32_t cont = builtIns(base, vectorGet(args, 1));

			if (!cont && base[0] != '\0') {
				int status;

				PID = fork();

				if (PID < 0) {
					printError("Error forking process", 0);
				}

				if (PID == 0) {
					// child
					if (execvp(base, (char**)args -> array) == -1) {
						printError("Command failure", 1);
					}
				} else {
					// parent
					wait(&status);
				}
			}
		}

		cleanUpCommand(cl);
	}

	/*_exit(EXIT_SUCCESS);*/
	return 0;
}
