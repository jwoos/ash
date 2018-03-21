#ifndef ASH_VECTOR_H
#define ASH_VECTOR_H


#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../common.h"
#include "../utils/math.h"
#include "common.h"


typedef struct Vector {
	uint64_t size;
	uint64_t capacity;

	void** array;
} Vector;


Vector* vectorConstruct(uint64_t);

void vectorDeconstruct(Vector* vector, void (*fn)(void*));

void vectorPush(Vector*, void*);

void* vectorPop(Vector*);

void* vectorGet(const Vector*, uint64_t);

void vectorSet(Vector*, uint64_t, void*);

void vectorInsert(Vector*, uint64_t, void*);

void vectorDelete(Vector*, uint64_t, void (*fn)(void*));

void vectorClear(Vector*, void (*fn)(void*));

void vectorResize(Vector*, enum Resize, uint64_t);


#endif
