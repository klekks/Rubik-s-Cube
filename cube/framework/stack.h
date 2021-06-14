#pragma once
#include "structures.h"

Stack* NewStack();
STRUCT_OBJ* StackPush(Stack* stack, void* val);
STRUCT_OBJ* StackPop(Stack* stack);
STRUCT_OBJ* StackPeek(Stack* stack, unsigned pos);
int StackEmpty(Stack* stack);
unsigned StackSize(Stack* stack);