#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

#include "shell.h"

int main(int argc, char* argv[]) {
	char* a = "asdf";
	char* b = "asdf";

	bool c = strEqual(a, b);

	if (c) {
		printf("true");
	} else {
		printf("false");
	}
}

