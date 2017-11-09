#include <stdlib.h>
#include <stdio.h>

#include <signal.h>
#include <unistd.h>

/*#include "data/hash-table.h"*/
#include "data/linked-list.h"
#include "data/vector.h"
#include "shell.h"


void testHashTable() {

}

void testLinkedList() {

}

void testVector() {
	int size = 100;

	Vector* vec = vectorConstruct(10);
	for (int i = 0; i < size; i++) {
		int* x = malloc(sizeof (int));
		*x = i;
		vectorPush(vec, x);
	}

	for (int i = 0; i < size; i++) {
		int* x = vectorGet(vec, i);
		printf("%d\n", *x);
		free(x);
	}
}

int main(int argc, char* argv[]) {
	testVector();
}
