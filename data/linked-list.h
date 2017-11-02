#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

/*
 * the ListNode is the actual list, I opted to wrap it in another struct
 * to avoid having to put the head/tail on each ListNode as that would be
 * highly inefficient. Also this way, other properties of the list as
 * a WHOLE can be recorded e.g. size
 */

// this should still be available
typedef struct ListNode {
	int data;
	struct ListNode* next;
} ListNode;

// ListNode wrapper
typedef struct List {
	ListNode* head;
	ListNode* tail;
	int size;
} List;

List* listConstruct(ListNode*);

void listDeconstruct(List*);

ListNode* listNodeInitialize(int, ListNode*);

void listNodeDeconstruct(ListNode*);

void listPrint(List*);

void listPush(List*, int);

ListNode* listPop(List*);

ListNode* listGetElement(List*, int);

void listSetElement(List*, int, int);

void listInsert(List*, int, int);

void listDelete(List*, int);

void listClear(List*);

#endif
