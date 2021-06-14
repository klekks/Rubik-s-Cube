#pragma once

#define NULL (void*) 0


struct _STRUCT_OBJ {
	void* val; // value
	struct _STRUCT_OBJ* next;
} ;


#define STRUCT_OBJ struct _STRUCT_OBJ

typedef struct {
	unsigned size;
	STRUCT_OBJ* head;
} Stack;


#include "stack.h"

