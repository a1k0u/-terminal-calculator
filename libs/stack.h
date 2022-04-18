#ifndef TERMINAL_CALCULATOR_STACK_H
#define TERMINAL_CALCULATOR_STACK_H

#include "string.h"

typedef struct Stack {
    STR* array;
    int capacity;
    int pointer;
} STACK;

STACK* add_to_stack(STACK* stack, STR* elem);
STR* take_head_stack(STACK* stack);
STR* pop_from_stack(STACK* stack);
STACK* del_stack(STACK* stack);
STACK* init_stack();

#endif //TERMINAL_CALCULATOR_STACK_H
