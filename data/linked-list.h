#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H


typedef struct ListNode {
	struct ListNode* next;
	struct ListNode* previous;
	void* data;
} ListNode;

// ListNode wrapper
typedef struct List {
	ListNode* head;
	ListNode* tail;
	uint64_t size;
} List;


List* listConstruct(ListNode*);

void listDeconstruct(List*);

ListNode* listNodeConstruct(void*, ListNode*, ListNode*);

void listNodeDeconstruct(ListNode*);

void listPushL(List*, void*);

void listPushR(List*, void*);

void* listPopL(List*);

void* listPopR(List*);

void* listGet(List*, uint64_t);

void listSet(List*, uint64_t, void*);

void listInsert(List*, uint64_t, void*);

void listDelete(List*, uint64_t);

void listClear(List*);


#endif
