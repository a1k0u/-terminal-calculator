#ifndef TERMINAL_CALCULATOR_STACK_H
#define TERMINAL_CALCULATOR_STACK_H

#include "str.h"
#include "node.h"

typedef struct Stack {
    NODE* array;
    int capacity, pointer;
} STACK;

STACK* add_to_stack(STACK* stack, NODE* elem);
NODE* take_head_stack(STACK* stack);
NODE* pop_from_stack(STACK* stack);
STACK* delete_stack(STACK* stack);
STACK* init_stack();

#endif //TERMINAL_CALCULATOR_STACK_H
