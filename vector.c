#include "vector.h"

static void increaseCapacity(Vector* vector) {
	vector -> capacity *= 2;

	vector -> arr = realloc(vector -> arr, sizeof(void*) * (vector -> capacity));
}

Vector* vectorInitialize(void) {
	Vector* vector = malloc(sizeof(Vector));

	vector -> size = 0;
	vector -> capacity = 1;
	vector -> arr = malloc(sizeof(void*));

	return vector;
}

void vectorDeconstruct(Vector* vector) {
	free(vector -> arr);
	free(vector);

	vector = NULL;
}

void vectorPush(Vector* vector, void* data) {
	if (vector -> size == vector -> capacity) {
		increaseCapacity(vector);
	}

	vector -> arr[vector -> size] = data;
	vector -> size++;
}

void* vectorPop(Vector* vector) {
	vector -> size--;

	void* data = vector -> arr[vector -> size];
	vector -> arr[vector -> size] = NULL;

	return data;
};

void* vectorGet(const Vector* vector, int index) {
	return vector -> arr[index];
};

void vectorSet(Vector* vector, int index, void* data) {
	vector -> arr[index] = data;
};

void vectorInsert(Vector* vector, int index, void* data) {
	if (vector -> size == vector -> capacity) {
		increaseCapacity(vector);
	}

	vector -> size++;

	for (int i = vector -> size - 1; i > index; i--) {
		vector -> arr[i] = vectorGet(vector, i - 1);
	}

	vectorSet(vector, index, data);
};

void deleteVector(Vector* vector, int index) {
	for (int i = index; i < vector -> size - 1; i++) {
		vector -> arr[i] = vectorGet(vector, i + 1);
	}

	vector -> size--;
};

void clearVector(Vector* vector) {
	free(vector -> arr);
	vector -> arr = malloc(sizeof(void*));
	vector -> size = 0;
	vector -> capacity = 1;
};
