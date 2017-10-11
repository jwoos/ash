#ifndef ASH_VECTOR_H
#define ASH_VECTOR_H

#include <stdlib.h>

typedef struct Vector {
	int size;
	int capacity;

	void** arr;
} Vector;

Vector* vectorInitialize(void);

void vectorDeconstruct(Vector* vector);

void vectorPush(Vector*, void*);

void* vectorPop(Vector*);

void* vectorGet(const Vector*, int);

void vectorSet(Vector*, int, void*);

void vectorInsert(Vector*, int, void*);

void deleteVector(Vector*, int);

void clearVector(Vector*);

#endif
