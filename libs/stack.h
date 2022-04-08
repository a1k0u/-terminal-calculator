#ifndef TERMINAL_CALCULATOR_STACK_H
#define TERMINAL_CALCULATOR_STACK_H

#include "string.h"

typedef struct Stack {
    STR** array;
    int capacity;
    int pointer;
} STACK;

STACK* init_stack();
STACK* del_stack(STACK* stack);
STACK* add_to_stack(STACK* stack, STR* elem);
STR* pop_from_stack(STACK* stack);

#endif //TERMINAL_CALCULATOR_STACK_H
