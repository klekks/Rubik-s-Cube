#include "stack.h"
#include <malloc.h>

Stack* NewStack() {
	Stack* stack = (Stack*)calloc(1, sizeof(Stack));
	return stack;
}

STRUCT_OBJ* StackPush(Stack* stack, void* val) {
	STRUCT_OBJ* obj = (STRUCT_OBJ*)calloc(1, sizeof(STRUCT_OBJ));
	if (!(obj && stack)) return NULL;
	obj->next = stack->head;
	stack->head = obj;
	obj->val = val;
	stack->size++;
	return obj;
}

STRUCT_OBJ* StackPop(Stack* stack) {
	if (!stack) return NULL;
	STRUCT_OBJ* obj = stack->head;
	if (stack->head) {
		stack->head = stack->head->next;
		stack->size--;
	}
	return obj;
}

STRUCT_OBJ* StackPeek(Stack* stack, unsigned pos) {
	if (!stack) return NULL;
	STRUCT_OBJ* elem = stack->head;
	while (pos-- && elem) elem = elem->next;
	return elem;
}

int StackEmpty(Stack* stack) {
	if (!stack || !stack->head) return 1;
	else return 0;
}

unsigned StackSize(Stack* stack) {
	if (!stack) return 0;
	return stack->size;
}