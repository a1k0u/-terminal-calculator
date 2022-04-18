#include "parsing.h"
#include <stdlib.h>
#include "stack.h"
#include <math.h>

STR oper[5][2] = {
        {"+", 1},
        {"-", 1},
        {"*", 2},
        {"/", 2},
        {"^", 3},
};

void added(STR** var, int* type) {
    *var = init_str();
    *type = NONE;
}

NODES_ARR* tokenization_string(STR* input) {
    int sign = 1, type = NONE;
    STACK* stack = init_stack();
    STR* variable = init_str();
    NODES_ARR* nodes_arr = init_nodes_arr();

    input = strip_str(input, ' ');
    for (int i = 0; i < input->len; ++i) {
        if ('0' <= input->word[i] && input->word[i]  <= '9' || input->word[i] == '.') {
            type = DOUBLE;
            variable = push_char(variable, input->word[i]);
        }
        else {
            if (type == DOUBLE) {
                nodes_arr = add_node_array(nodes_arr, create_node(variable, type));
                added(&variable, &type);
            }

            variable = push_char(variable, input->word[i]);
            for (int j = 0; j < sizeof(oper) / sizeof(STR); ++j) {
                if (compare_str(oper[j], variable)) {
                    while (stack->pointer && variable->len <= take_head_stack(stack)->len)
                        nodes_arr = add_node_array(nodes_arr, create_node(pop_from_stack(stack), OPERATION));
                    stack = add_to_stack(stack, variable);
                    added(&variable, &type);
                    break;
                }
            }
        }
    }
    if (type == DOUBLE)
        nodes_arr = add_node_array(nodes_arr, create_node(variable, type));

    while (stack->pointer)
        nodes_arr = add_node_array(nodes_arr, create_node(pop_from_stack(stack), OPERATION));


    stack = del_stack(stack);
    variable = del_str(variable);

    return nodes_arr;
}

int token_processing(NODES_ARR* tokens) {
    int index = 0;
    while (tokens->length != 1) {
        NODE obj = tokens->array[index];
        if (obj.type == OPERATION) {
            long double a = tokens->array[index - 1].real, b = tokens->array[index - 2].real, res;
            if (obj.action == '+')
                res = a + b;
            else if (obj.action == '-')
                res = a - b;
            else if (obj.action == '*')
                res = a * b;
            else if (obj.action == '/')
                res = a / b;
            else
                res = a * a;

            NODE* new_node = (NODE*)malloc(sizeof(NODE));
            new_node->type = DOUBLE;
            new_node->real = res;
            tokens = insert_node_array(tokens, new_node, index);
            index = 0;
        }

        index++;
    }

    return tokens->array[0].real;
}