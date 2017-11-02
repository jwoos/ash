#include <stdlib.h>
#include <stdio.h>

#include "linked-list.h"


List* listConstruct(SingleListNode* node) {
	List* list = malloc(sizeof(List));
	if (!list) {
		return NULL;
	}

	if (!node) {
		list -> head = NULL;
		list -> tail = NULL;
		list -> size = 0;
	} else {
		list -> head = node;
		list -> tail = node;
		list -> size = 1;
	}

	return list;
}

void listDeconstruct(List* list) {
	SingleListNode* current = list -> head;

	while (current != list -> tail) {
		SingleListNode* next = current -> next;

		free(current);

		current = next;
	}

	free(list);
	list = NULL;
}

SingleListNode* listNodeInitialize(int data, SingleListNode* next) {
	SingleListNode* node = malloc(sizeof(SingleListNode));
	if (!node) {
		return NULL;
	}

	node -> data = data;
	node -> next = next ? next : NULL;

	return node;
}

void listNodeDeconstruct(SingleListNode* node) {
	free(node);
}

void listPrint(List* list) {
	SingleListNode* current = list -> head;

	while (current != NULL) {
		printf("%d -> ", current -> data);
		current = current -> next;
	}

	printf("\n");
}

void listPush(List* list, int data) {
	SingleListNode* tail = list -> tail;

	SingleListNode* newElem = listNodeInitialize(data, NULL);

	tail -> next = newElem;
	list -> tail = newElem;
	list -> size++;
}

SingleListNode* listPop(List* list) {
	SingleListNode* tail = list -> tail;

	SingleListNode* current = list -> head;
	while (current -> next -> next != NULL) {
		current = current -> next;
	}

	current -> next = NULL;
	list -> tail = current;
	list -> size--;

	return tail;
}

SingleListNode* listGetElement(List* list, int index) {
	if (index >= list -> size) {
		printf("Element not found at index %d - outside of range\n", index);
		return NULL;
	}

	SingleListNode* node = list -> head;

	int i = 0;
	while (i < index) {
		if (node != NULL) {
			i++;
			node = node -> next;
		} else {
			printf("Element not found at index %d outside of range\n", index);
			return NULL;
		}
	}

	return node;
}

void listSetElement(List* list, int index, int newData) {
	SingleListNode* atIndex = listGetElement(list, index);

	if (atIndex == NULL) {
		printf("Not setting - aborting...\n");
		return;
	}

	atIndex -> data = newData;
}

void listInsert(List* list, int index, int newData) {
	SingleListNode* atIndex = listGetElement(list, index - 1);

	SingleListNode* newNode = listNodeInitialize(newData, atIndex -> next);
	atIndex -> next = newNode;

	list -> size++;
}

void listDelete(List* list, int index) {
	SingleListNode* prevIndex = listGetElement(list, index - 1);
	SingleListNode* temp = prevIndex -> next;

	prevIndex -> next = prevIndex -> next -> next;

	free(temp);
	list -> size--;
}

void listClear(List* list) {
	SingleListNode* current = list -> head;
	SingleListNode* tempHolder[list -> size];

	int i = 0;
	while (current != NULL) {
		tempHolder[i] = current;
		current = current -> next;
		i++;
	}

	for (int i = 0; i < list -> size; i++) {
		free(tempHolder[i]);
	}

	list -> head = NULL;
	list -> tail = NULL;
	list -> size = 0;
}
