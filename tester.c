#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

#include "sds/sds.h"
#include "utils.h"

int main(int argc, char* argv[]) {
	sds aString = sdsnew("Hello!\n");
	writeStdout(aString, sdslen(aString));

	_exit(EXIT_SUCCESS);
}

