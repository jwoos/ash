#include "string.h"


char** generateEmptyStringArr() {
	char** buffArr = malloc(sizeof(char*));
	buffArr[0] = malloc(sizeof(char));
	buffArr[0][0] = '\0';

	return buffArr;
}

// not binary safe
int countChars(char* buf) {
	int index = 0;

	do {
		index++;
	} while (buf[index] != '\0');

	return index;
}

void freeArray(void** arr, int size) {
	for (int i = 0; i < size; i++) {
		free(arr[i]);
	}

	free(arr);
}

bool strEqual(char* a, char* b) {
	int aLength = strlen(a);
	int bLength = strlen(b);

	if (aLength != bLength) {
		return false;
	}

	for (int i = 0; i < aLength; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}

	return true;
}
