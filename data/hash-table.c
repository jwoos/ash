#include "hash-table.h"


HashTable* hashTableConstruct(uint64_t size) {
	HashTable* htPtr = malloc(sizeof (*htPtr));

	if (!htPtr) {
		return NULL;
	}

	HashTable ht = *htPtr;

	ht.size = 0;
	ht.capacity = 10;
	ht.store = malloc(sizeof (HashTableNode*) * ht.capacity);

	return htPtr;
}

void hashTableDeconstruct(HashTable* ht) {
	for (uint64_t i = 0; i < ht -> capacity; i++) {
	}

	free(ht -> store);
	free(ht);
}

void hashTableSet(HashTable* ht, char* key, void* data) {
	uint64_t hash = hashSBDM(key);
	uint64_t index = hash % (ht -> capacity);
	HashTableNode current = ht -> store[index];

	/* performace degradation due to high load
	 * increase capacity and rehash
	 */
	if ((double)ht -> size / ht -> capacity >= 0.65) {
		hashTableResize(ht);
		hashTableRehash(ht);
	}

	if (current.size) {
		bool set = false;
		for (uint64_t i = 0; i < current.size; i++) {
			HashTableNode* node = vectorGet(current, i);
			if (node -> key == key) {
				node -> data = data;
				set = true;
				break;
			}
		}

		if (!set) {
			HashTableNode* node = hashTableNodeConstruct(key, data);
			vectorPush(current, node)
		}
	} else {
		HashTableNode* node = hashTableNodeConstruct(key, data);
		vectorPush(current, node);
	}
}

void* hashTableGet(char* key) {
	uint64_t hash = hashSBDM(key);
	uint64_t index = hash % (ht -> capacity);
	Vector current = ht -> store[index];
	void* data = NULL;

	if (current -> size) {
		for (uint64_t i = 0; i < current.size; i++) {
			HashTableNode* node = vectorGet(current, i);
			if (node -> key == key) {
				data = node -> data;
			}
		}
	}

	return data;
}

static void hashTableRehash(HashTable* ht) {
}

void hashTableResize(HashTable* ht, enum Resize action, uint32_t factor) {
	uint64_t proposedSize;
	uint64_t currentSize = ht -> size;

	switch (action) {
		case ADD:
			proposedSize = currentSize + factor;
			break;

		case MULTIPLY:
			proposedSize = currentSize * factor;
			break;

		case SUBTRACT:
			proposedSize = max(currentSize - factor, 0);
			break;

		case DIVIDE:
			proposedSize = currentSize / factor;
			break;

		case SET:
			proposedSize = factor;
			break;
	}

	ht -> capacity = proposedSize;
	vectorResize(ht -> store, MULTIPLY, factor);
}

HashTableNode* hashTableNodeConstruct(char* key, void* data) {
	HashTableNode* hmNode = malloc(sizeof *hmNode);
	hmNode -> key = key;
	hmNode -> data = data;

	return hmNode;
}

void hashTableNodeDeconstruct(HashTableNode* hmNode) {
	free(hmNode);
}
