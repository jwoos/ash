#ifndef ASH_VECTOR_H
#define ASH_VECTOR_H


#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../utils/math.h"

#include "common.h"


typedef struct Vector {
	uint64_t size;
	uint64_t capacity;

	void** array;
} Vector;


Vector* vectorConstruct(uint64_t);

void vectorDeconstruct(Vector* vector);

void vectorPush(Vector*, void*);

void* vectorPop(Vector*);

void* vectorGet(const Vector*, uint64_t);

void vectorSet(Vector*, uint64_t, void*);

void vectorInsert(Vector*, uint64_t, void*);

void vectorDelete(Vector*, uint64_t);

void vectorClear(Vector*);

void vectorResize(Vector*, enum Resize, uint64_t);


#endif
