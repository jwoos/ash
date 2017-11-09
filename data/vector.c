#include "vector.h"


Vector* vectorConstruct(uint64_t cap) {
	Vector* vector = malloc(sizeof (Vector));

	if (!cap) {
		cap = ASH_DATA_DEFAULT_SIZE;
	}

	vector -> size = 0;
	vector -> capacity = cap;
	vector -> arr = malloc(sizeof (void*) * (vector -> capacity));

	return vector;
}

void vectorDeconstruct(Vector* vector) {
	for (uint64_t i = 0; i < vector -> size - 1; i++) {
		free(vector -> arr[i]);
	}

	free(vector -> arr);
	free(vector);
}

void vectorPush(Vector* vector, void* data) {
	if (vector -> size == vector -> capacity) {
		vectorResize(vector, MULTIPLY, ASH_DATA_INCREASE_FACTOR);
	}

	vector -> arr[vector -> size] = data;
	vector -> size++;
}

void* vectorPop(Vector* vector) {
	vector -> size--;

	void* data = vector -> arr[vector -> size - 1];
	vector -> arr[vector -> size] = NULL;

	return data;
}

void* vectorGet(const Vector* vector, uint64_t index) {
	return vector -> arr[index];
}

void vectorSet(Vector* vector, uint64_t index, void* data) {
	vector -> arr[index] = data;
}

void vectorInsert(Vector* vector, uint64_t index, void* data) {
	if (vector -> size == vector -> capacity) {
		vectorResize(vector, MULTIPLY, ASH_DATA_INCREASE_FACTOR);
	}

	vector -> size++;

	for (uint64_t i = vector -> size - 1; i > index; i--) {
		vector -> arr[i] = vectorGet(vector, i - 1);
	}

	vectorSet(vector, index, data);
}

void vectorDelete(Vector* vector, uint64_t index) {
	for (uint64_t i = index; i < vector -> size - 1; i++) {
		vector -> arr[i] = vectorGet(vector, i + 1);
	}

	vector -> size--;
}

void vectorClear(Vector* vector) {
	for (uint64_t i = 0; i < vector -> size - 1; i++) {
		free(vector -> arr[i]);
	}
	vector -> arr = realloc(sizeof (void*), ASH_DATA_DEFAULT_SIZE);
	vector -> size = 0;
	vector -> capacity = ASH_DATA_DEFAULT_SIZE;
}

void vectorResize(Vector* vector, enum Resize action, uint64_t amount) {
	uint64_t currentSize = vector -> size;
	uint64_t proposedSize;

	switch (action) {
		case ADD:
			proposedSize = currentSize + amount;
			break;

		case MULTIPLY:
			proposedSize = currentSize * amount;
			break;

		case SUBTRACT:
			proposedSize = max(currentSize - amount, 0);
			break;

		case DIVIDE:
			proposedSize = currentSize / amount;
			break;

		case SET:
			proposedSize = amount;
			break;
	}

	vector -> capacity = proposedSize;
	vector -> size = min(vector -> capacity, vector -> size);
	vector -> arr = realloc(vector -> arr, sizeof (*(vector -> arr)) * (vector -> capacity));
}
