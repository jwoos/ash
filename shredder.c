#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeoutHandler(int signum) {
	char message[] = "Timed out - aborting...";
	write(stdout, message, 25);
	_exit(1);
}

int main(int argc, char* argv[]) {
	int seconds = 0;

	if (argv[1] != "") {
		seconds = atoi(argv[1]);
	}

	while (1) {

	}
}
