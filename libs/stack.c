#include "stack.h"
#include <stdlib.h>

STACK* init_stack() {
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->array = (STR**)malloc(sizeof(STR*));
    stack->capacity = stack->pointer = 0;

    return stack;
}

STACK* add_to_stack(STACK* stack, STR* elem) {
    if (stack->capacity == stack->pointer) {
        stack->capacity = stack->capacity * 2 + 1;
        stack->array = (STR**)realloc(stack->array,sizeof(STR*) * stack->capacity);
    }

    stack->array[stack->pointer++] = elem;
    return stack;
}

STR* pop_from_stack(STACK* stack) {
    return stack->array[--stack->pointer];
}

STACK* del_stack(STACK* stack) {
    for (int i = 0; i < stack->pointer; ++i)
        stack->array[i] = del_str(stack->array[i]);
    free(stack->array);
    stack->capacity = stack->pointer = 0;
    stack = NULL;

    return stack;
}