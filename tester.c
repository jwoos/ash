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


void testHashTable() {

}

void testLinkedList() {

}

void testVector() {
	testVectorBasic();
	testVectorAutoResize();
	testVectorResize();
	testVectorInsertDelete();

	while (1) {}
}

int main(int argc, char* argv[]) {
	testVector();
}
