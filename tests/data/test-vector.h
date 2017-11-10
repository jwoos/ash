#include "../../data/vector.h"


static int size = 100;

void testVectorBasic() {
	Vector* vec = vectorConstruct(size);
	vectorDeconstruct(vec);
}

void testVectorAutoResize() {
	Vector* vec = vectorConstruct(1);

	assert(vec -> size == 0);
	assert(vec -> capacity == 1);

	for (int i = 0; i < size; i++) {
		int* x = malloc(sizeof (int));
		*x = i;
		vectorPush(vec, x);
	}

	assert(vec -> size == 100);
	assert(vec -> capacity == 128);

	vectorDeconstruct(vec);
}

void testVectorResize() {
	Vector* vec = vectorConstruct(size);
	vectorResize(vec, MULTIPLY, 2);
	assert(vec -> capacity == size * 2);
	vectorResize(vec, SUBTRACT, 100);
	assert(vec -> capacity == size);
	vectorResize(vec, ADD, 100);
	assert(vec -> capacity == size * 2);
	vectorResize(vec, DIVIDE, 2);
	assert(vec -> capacity == size);
	vectorDeconstruct(vec);
}

void testVectorInsertDelete() {
	Vector* vec = vectorConstruct(size);

	for (int i = 0; i < 10; i++) {
		int* temp = malloc(sizeof (int));
		*temp = i + 1;
		vectorPush(vec, temp);
	}

	int* x = malloc(sizeof (int));
	*x = 100;
	vectorInsert(vec, 0, x);

	assert(vectorGet(vec, 0) == x);
	assert(vec -> capacity == size);

	vectorDelete(vec, 0);
	vectorDeconstruct(vec);
}
