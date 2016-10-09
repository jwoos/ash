#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

#include "utils.h"

int main(int argc, char* argv[]) {
	writeStdout("test", 4);

	_exit(EXIT_SUCCESS);
}

