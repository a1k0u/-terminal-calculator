#ifndef TERMINAL_CALCULATOR_STACK_H
#define TERMINAL_CALCULATOR_STACK_H

#include "str.h"

typedef struct Stack {
    STR* array;
    int capacity, pointer;
} STACK;

STACK* add_to_stack(STACK* stack, STR* elem);
STR* take_head_stack(STACK* stack);
STR* pop_from_stack(STACK* stack);
STACK* delete_stack(STACK* stack);
STACK* init_stack();

#endif //TERMINAL_CALCULATOR_STACK_H
