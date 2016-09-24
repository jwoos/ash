#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

#include "utils.h"

void handler(int signum) {
	char message[] = "Timed out - aborting...\n";
	writeStdout(message, sizeof message);

	char* stdinRead = readStdin();
	writeStdout(stdinRead, 100);
	_exit(0);
}

int main(int argc, char* argv[]) {
	signal(SIGALRM, handler);
	alarm(1);
	while(1);
}

