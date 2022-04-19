#include "parsing.h"
#include "stack.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>


NODES_ARRAY* tokenization_string(STR* input) {
    NODES_ARRAY* nodes_arr = init_nodes_arr();
    STACK* stack = init_stack();
    STR* variable = init_str();

    input = delete_symbols(input, ' ');

    if (input->data[0] == '-' || input->data[0] == '+') {
        STR *temporary = init_str();
        strcat(temporary->data, "0");
        strcat(temporary->data, input->data);
        input = delete_str(input);

        input = temporary;
    }

    for (int i = 0; i < strlen(input->data); ++i) {
        if (isdigit(input->data[i]) || input->data[i] == '.') {
            if (variable->str_info != FUNCTION)
                variable->str_info = DOUBLE;

            strncat(variable->data, &input->data[i], 1);
        }
        else if (ispunct(input->data[i])) {
            if (variable->str_info == DOUBLE) {
                nodes_arr = add_node_array(
                        nodes_arr, create_node(variable, DOUBLE)
                        );
                variable = init_str();
            }
            else if (variable->str_info == VARIABLE) {
                if (strncmp(&input->data[i], "(", 1)) {
                    for (int k = 0; k < sizeof(BUILT) / sizeof(STR); ++k) {
                        if (strcmp(BUILT[k]->data, variable->data)) {
                            variable->str_info = FUNCTION;
                        }
                    }

                    if (variable->str_info == FUNCTION)
                        continue;
                    else {} // except!
                }
                else {
                    for (int k = 0; k < sizeof(CONSTANT) / sizeof(STR); ++k)
                        if (strcmp(CONSTANT[k]->data, variable->data)) {
                            int type = DOUBLE;
                            if (strcmp(CONSTANT[k]->data, "j"))
                                type = COMPLEX;

                            STR* constant = init_str();
                            sprintf(constant->data, "%Lf", CONSTANT[k]->str_info);
                            nodes_arr = add_node_array(
                                    nodes_arr, create_node(constant, type)
                                    );

                            variable->str_info = CONST;
                        }

                    if (variable->str_info == CONST) {
                        variable = delete_str(variable);
                        variable = init_str();
                        continue;
                    }

                    // go to hash table
                }
            }
            else if (variable->str_info == FUNCTION) {
                if (strncmp(&input->data[i], ")", 1)) {

                }
                else {} // except
            }

            for (int j = 0; j < sizeof(ACTIONS) / sizeof(STR); ++j) {
                if (strncmp(&input->data[i], ACTIONS[j]->data, 1)) {
                    if (strcmp(ACTIONS[j]->data, "("))
                        add_to_stack(stack, ACTIONS[j]);
                    else if (strcmp(ACTIONS[j]->data, ")")) {
                        while (!strcmp(take_head_stack(stack)->data, "("))
                            nodes_arr = add_node_array(
                                    nodes_arr,create_node(pop_from_stack(stack), OPERATION)
                               );
                        delete_str(pop_from_stack(stack));
                    }
                    else {
                        while (stack->pointer && ACTIONS[j]->str_info <= take_head_stack(stack)->str_info) {
                            nodes_arr = add_node_array(
                                    nodes_arr, create_node(pop_from_stack(stack), OPERATION)
                                    );
                        }
                        stack = add_to_stack(stack, ACTIONS[j]);
                    }
                }
            }
        }
        else if (isalpha(input->data[i])) {
            if (strncmp(&input->data[i], "j", 1) && variable->str_info == DOUBLE) {
                nodes_arr = add_node_array(
                        nodes_arr, create_node(variable, COMPLEX)
                        );
                variable = init_str();
                continue;
            }

            strncmp(variable, &input->data[i]);
            variable->str_info = VARIABLE;
        }
    }

    if (type == DOUBLE)
        nodes_arr = add_node_array(nodes_arr, create_node(variable, type));

    while (stack->pointer)
        nodes_arr = add_node_array(nodes_arr, create_node(pop_from_stack(stack), OPERATION));


    stack = del_stack(stack);
    variable = del_str(variable);

    for (int i = 0; i < nodes_arr->length; ++i)
        if (nodes_arr->array[i].type == DOUBLE)
            printf("%Lf ", nodes_arr->array[i].real);
        else
            printf("%c ", nodes_arr->array[i].action);
    printf("\n");

    return nodes_arr;
}

long double token_processing(NODES_ARR* tokens) {
    int index = 0;
    while (tokens->length != 1) {
        NODE obj = tokens->array[index];
        if (obj.type == OPERATION) {
            long double a = tokens->array[index - 2].real, b = tokens->array[index - 1].real, res;
            if (obj.action == '+')
                res = a + b;
            else if (obj.action == '-')
                res = a - b;
            else if (obj.action == '*')
                res = a * b;
            else if (obj.action == '/')
                res = a / b;
            else
                res = powl(a, b);

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