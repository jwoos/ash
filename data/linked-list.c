#include <stdlib.h>
#include <stdio.h>

#include "linked-list.h"


List* listConstruct(ListNode* node) {
	List* list = malloc(sizeof (List));

	if (!list) {
		return NULL;
	}

	if (!node) {
		list -> head = NULL;
		list -> tail = NULL;
		list -> size = 0;
	} else {
		node -> next = NULL;
		node -> previous = NULL;
		list -> head = node;
		list -> tail = node;
		list -> size = 1;
	}

	return list;
}

void listDeconstruct(List* list) {
	ListNode* current = list -> head;

	while (current != list -> tail) {
		ListNode* next = current -> next;

		listNodeDeconstruct(current);

		current = next;
	}

	free(list);
}

ListNode* listNodeConstruct(void* data, ListNode* prev, ListNode* next) {
	ListNode* node = malloc(sizeof (ListNode));

	if (!node) {
		return NULL;
	}

	node -> data = data;
	node -> next = next ? next : NULL;
	node -> previous = prev ? prev : NULL;

	return node;
}

void listNodeDeconstruct(ListNode* node) {
	free(node -> data);
	free(node);
}

void listPush(List* list, void* data) {
	ListNode* tail = list -> tail;

	ListNode* newElem = listNodeConstruct(data, tail, NULL);
	tail -> next = newElem;

	list -> tail = newElem;
	list -> size++;
}

void* listPop(List* list) {
	ListNode* tail = list -> tail;
	ListNode* previous = tail -> previous;

	previous -> next = NULL;
	list -> tail = previous;
	list -> size--;

	void* data = tail -> data;
	free(tail);

	return data;
}

void* listGet(List* list, uint64_t index) {
	if (index >= list -> size) {
		return NULL;
	}

	ListNode* node;
	uint64_t i;
	if (index <= list -> size / 2) {
		node = list -> head;
		i = 0;

		while (i < index) {
			if (node != NULL) {
				i++;
				node = node -> next;
			}
		}
	} else {
		node = list -> tail;
		i = list -> size - 1;

		while (i > index) {
			if (node != NULL) {
				i--;
				node = node -> previous;
			}
		}
	}

	void* data = node -> data;
	free(data);

	return data;
}

void listSet(List* list, uint64_t index, void* newData) {
	ListNode* atIndex = listGet(list, index);

	if (atIndex == NULL) {
		printf("Not setting - aborting...\n");
		return;
	}

	atIndex -> data = newData;
}

void listInsert(List* list, uint64_t index, void* newData) {
	ListNode* atIndex = listGet(list, index - 1);

	ListNode* newNode = listNodeConstruct(newData, atIndex -> next);
	atIndex -> next = newNode;

	list -> size++;
}

void listDelete(List* list, uint64_t index) {
	ListNode* prevIndex = listGet(list, index - 1);
	ListNode* temp = prevIndex -> next;

	prevIndex -> next = prevIndex -> next -> next;

	free(temp);
	list -> size--;
}

void listClear(List* list) {
	ListNode* current = list -> head;
	ListNode* tempHolder[list -> size];

	uint64_t i = 0;
	while (current != NULL) {
		tempHolder[i] = current;
		current = current -> next;
		i++;
	}

	for (uint64_t i = 0; i < list -> size; i++) {
		free(tempHolder[i]);
	}

	list -> head = NULL;
	list -> tail = NULL;
	list -> size = 0;
}
