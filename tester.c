#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*#include "data/hash-table.h"*/
#include "data/linked-list.h"
#include "data/vector.h"
#include "shell.h"

#include "tests/data/test-vector.h"


typedef struct Test {
	void* data;
} Test;

void testDeconstruct(Test* t) {
	free(t -> data);
	free(t);
}

void testHashTable() {

}

void testLinkedList() {

}

void testVector() {
	testVectorBasic();
	testVectorAutoResize();
	testVectorResize();
	testVectorInsertDelete();

	Vector* vec = vectorConstruct(10);
	Test* x = malloc(sizeof (*x));
	int* i = malloc(sizeof (*i));
	x -> data = i;
	vectorPush(vec, x);
	vectorDeconstruct(vec, &testDeconstruct);
}

int main(int argc, char* argv[]) {
	testVector();
}
