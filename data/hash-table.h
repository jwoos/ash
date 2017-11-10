#ifndef OPEN_HASH_MAP_H
#define OPEN_HASH_MAP_H


#include <stdlib.h>

#include "../vendor/hash.h"

#include "common.h"
#include "vector.h"
#include "linked-list.h"


typedef struct HashTableNode {
	uint64_t hash;
	char* key;
	void* data;
} HashTableNode;

typedef struct HashTable {
	uint32_t size;
	uint32_t capacity;
	HashTableNode* store;
} HashTable;


HashTable* hashTableConstruct(uint64_t);

void hashTableDeconstruct(HashTable*);

void hashTableSet(HashTable*, char*, void*);

void* hashTableGet(HashTable*, char*);

void hashTableResize(HashTable*, enum Resize, uint64_t);

HashTableNode* hashTableNodeConstruct(char*, void*);

void hashTableNodeDeconstruct(HashTableNode*);


#endif
