#include "shell.h"

// TODO figure out a better way to pass around this
int PID;

void setPID(int childPID) {
	PID = childPID;
}

int getPID() {
	return PID;
}

void timeoutHandler(int signum) {
	printError("Timed out, aborting...", 0);

	kill(PID, SIGKILL);
}

void prompt() {
	writeStdout("shell > ", 9);
}
