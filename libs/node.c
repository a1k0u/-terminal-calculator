#include "node.h"
#include "stack.h"
#include <stdlib.h>

NODE* create_node(int is_num, long double image, long double real, char operation) {
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->is_number_flag = is_num;
    node->image = image;
    node->real = real;
    node->operation = operation;

    return node;
}

NODES_ARR* init_nodes_arr() {
    NODES_ARR* nodes_arr = (NODES_ARR*)malloc(sizeof(NODES_ARR));
    nodes_arr->array = (NODE**)malloc(sizeof(NODE*));
    nodes_arr->capacity = nodes_arr->length = 0;

    return nodes_arr;
}

NODES_ARR* delete_nodes_arr(NODES_ARR* nodes_arr) {
    for (int i = 0; i < nodes_arr->length; ++i)
        free(nodes_arr->array[i]);
    free(nodes_arr->array);
    nodes_arr->length = nodes_arr->capacity = 0;
    free(nodes_arr);

    return NULL;
}

NODES_ARR* add_node_array(NODES_ARR* nodes_arr, NODE* node) {
    if (nodes_arr->length == nodes_arr->capacity) {
        nodes_arr->capacity = nodes_arr->capacity * 2 + 1;
        nodes_arr->array = (NODE**)malloc(sizeof(NODE*));
    }

    nodes_arr->array[nodes_arr->length++] = node;
    return nodes_arr;
}


NODES_ARR* tokenization_string(STR* input) {
    STACK* stack = init_stack();
    STR* variable = init_str();
    STR* type = variable_type[NONE];

    input = strip_str(input, ' ');
    for (int i = 0; i < input->len; ++i) {
        if ('0' <= input->word[i] && input->word[i]  <= '9' || input->word[i] == '.') {
            if (compare_str(type, variable_type[VAR])) {
                continue;
            }

            type = variable_type[NUM];
            variable = push_char(variable, input->word[i]);
        }

        if ('a' <= input->word[i] && input->word[i] <= 'z' ||
                    'A' <= input->word[i] && input->word[i] <= 'Z') {
            if (compare_str(type, variable_type[NUM])) {}
        }

        if (variable->len == 1)
            for (int j = 0; j < sizeof(operations) / sizeof(STR); ++j)
                if (compare_str(variable, operations[j])) {
                    stack = add_to_stack(stack, variable);

                    variable = del_str(variable);
                    variable = init_str();
                }

    }

    return NULL;
}
