#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

#include "shell.h"

int main(int argc, char* argv[]) {
	Vector* v = vectorInitialize();
	int* a = malloc(sizeof(int));
	*a = 10;
	char* b = malloc(sizeof(char));
	*b = 'c';
	vectorPush(v, a);
	vectorPush(v, b);

	printf("%d\n", v -> size);
	printf("%d\n", v -> capacity);
	printf("%d\n", *(int*) vectorGet(v, 0));
	printf("%c\n", *(char*) vectorGet(v, 1));

	_exit(EXIT_SUCCESS);
}

