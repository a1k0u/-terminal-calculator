#include "stack.h"
#include <stdlib.h>

STACK* init_stack() {
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->array = (NODE*)malloc(sizeof(NODE));
    stack->capacity = stack->pointer = 0;
    return stack;
}

NODE* take_head_stack(STACK* stack) {
    return &stack->array[stack->pointer - 1];
}

STACK* add_to_stack(STACK* stack, NODE* element) {
    if (stack->pointer == stack->capacity) {
        stack->capacity = stack->capacity * 2 + 1;
        stack->array = (NODE*)realloc(
                stack->array,sizeof(NODE) * stack->capacity
                );
    }

    stack->array[stack->pointer++] = *element;
    return stack;
}

NODE* pop_from_stack(STACK* stack) {
    return &stack->array[--stack->pointer];
}

STACK* delete_stack(STACK* stack) {
    for (int i = 0; i < stack->pointer; ++i)
        stack->array[i] = *delete_node(&stack->array[i]);
    free(stack->array);
    free(stack);
    return NULL;
}
