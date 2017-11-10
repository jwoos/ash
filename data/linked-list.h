#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H


typedef struct ListNode {
	uint64_t data;
	struct ListNode* next;
	struct ListNode* previous;
} ListNode;

// ListNode wrapper
typedef struct List {
	ListNode* head;
	ListNode* tail;
	uint64_t size;
} List;

List* listConstruct(ListNode*);

void listDeconstruct(List*);

ListNode* listNodeInitialize(uint64_t, ListNode*);

void listNodeDeconstruct(ListNode*);

void listPrint(List*);

void listPush(List*, uint64_t);

ListNode* listPop(List*);

ListNode* listGetElement(List*, uint64_t);

void listSetElement(List*, uint64_t, uint64_t);

void listInsert(List*, uint64_t, uint64_t);

void listDelete(List*, uint64_t);

void listClear(List*);

#endif
