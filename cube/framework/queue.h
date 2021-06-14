#pragma once


typedef struct Node {
	struct Node* next;
	struct Node* prev;
	void* data;
} Node;

typedef struct Queue {
	struct Node* head;
	struct Node* tail;
	int size;
} Queue;

void QueuePush(Queue*, void*);
void* QueuePop(Queue*);
void QueueClear(Queue*);