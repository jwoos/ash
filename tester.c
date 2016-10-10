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
	sds c = sdsnew("hello");

	vectorPush(v, a);
	vectorPush(v, b);
	vectorPush(v, c);

	printf("%d\n", v -> size);
	printf("%d\n", v -> capacity);
	printf("%d\n", *(int*) vectorGet(v, 0));
	printf("%c\n", *(char*) vectorGet(v, 1));
	printf("%s\n", (sds) vectorGet(v, 2));

	_exit(EXIT_SUCCESS);
}

