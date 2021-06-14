#include "queue.h"
#include <malloc.h>

void QueuePush(Queue* queue, void* data) {
	if (!queue) return;
	Node* new_element = calloc(1,sizeof(Node));
	if (!new_element) return;
	new_element->data = data;
	new_element->prev = queue->tail;
	if (queue->tail) queue->tail->next = new_element;
	else queue->head = new_element;
	queue->tail = new_element;
	queue->size++;
}

void* QueuePop(Queue* queue) {
	if (!queue) return -1;
	if (!queue->head) return -1;
	void* res = queue->head->data;
	Node* next = queue->head->next;
	free(queue->head);
	queue->head = next;
	queue->size--;
	if (queue->size == 0) queue->tail = NULL;
	return res;
}

void QueueClear(Queue* queue) {
	while (queue->size > 0) QueuePop(queue);
}