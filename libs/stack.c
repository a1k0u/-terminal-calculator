#include "stack.h"
#include <stdlib.h>

STACK* init_stack() {
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->array = (STR*)malloc(sizeof(STR));
    stack->capacity = stack->pointer = 0;
    return stack;
}

STR* take_head_stack(STACK* stack) {
    return &stack->array[stack->pointer - 1];
}

STACK* add_to_stack(STACK* stack, STR* element) {
    if (stack->capacity == stack->pointer) {
        stack->capacity = stack->capacity * 2 + 1;
        stack->array = (STR*)realloc(
                stack->array,sizeof(STR) * stack->capacity
                );
    }

    stack->array[stack->pointer++] = *element;
    return stack;
}

STR* pop_from_stack(STACK* stack) {
    return &stack->array[--stack->pointer];
}

STACK* delete_stack(STACK* stack) {
    for (int i = 0; i < stack->pointer; ++i)
        stack->array[i] = *delete_str(&stack->array[i]);
    free(stack->array);
    free(stack);
    return NULL;
}
