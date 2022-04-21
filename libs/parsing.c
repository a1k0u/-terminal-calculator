#include "parsing.h"
#include "stack.h"
#include <ctype.h>
#include <stdio.h>
#include <math.h>


STR BUILT[][2] = {
        {"sin",   FUN, 3},
        {"cos",   FUN, 3},
        {"ln",    FUN, 2},
        {"sqrt",  FUN, 4},
        {"exp",   FUN, 3},
        {"real",  FUN, 4},
        {"imag",  FUN, 4},
        {"mag",   FUN, 3},
        {"phase", FUN, 5},
};


STR ACTIONS[][2] = {
        {"+", FIRST, 1},
        {"-", FIRST, 1},
        {"*", SECOND, 1},
        {"/", SECOND, 1},
        {"^", THIRD, 1},
        {"(", EMPTY, 1},
        {")", EMPTY, 1},
};

int get_priority(STR* operation) {
    for (int i = 0; i < 7; ++i)
        if (compare_str(operation, ACTIONS[i]))
            return ACTIONS[i]->info;
}

NODES_ARRAY* tokenization_string(STR* input) {
    NODES_ARRAY* nodes_array = init_nodes_array();
    STR* var = init_str();
    int sign = 1;

    input = delete_symbols(input, ' ');
    for (int i = 0; i < input->len; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (input->data[i] == ACTIONS[j]->data[0]) {
                if ((input->data[i] == '+' || input->data[i] == '-')
                    && var->info == NON && (!nodes_array->length ||
                    get_last_node(nodes_array)->value->info == OPN)) {

                    if (ACTIONS[j]->data[0] == '-')
                        sign *= -1;
                    else if (ACTIONS[j]->data[0] == '+')
                        sign *= 1;
                    else
                        printf("syntax!\n");
                    break;
                }

                if (var->len && var->data[0] == '.')
                    printf("syntax!\n");

                if (var->len) {
                    if (var->info == FUN && input->data[i] != '(')
                        var->info = VAR;
                    add_node_array(nodes_array, create_node(var, sign));
                    var = init_str();
                    sign = 1;
                }

                STR* tmp = init_str();
                copy_str(tmp, ACTIONS[j]);
                tmp->info = OPN;
                add_node_array(nodes_array, create_node(tmp, sign));
            }
        }

        if (isdigit(input->data[i]) || input->data[i] == '.') {
            if (var->info != VAR && var->info != FUN)
                var->info = DBL;
            push_str(var, input->data[i]);
        }
        else if (isalpha(input->data[i])) {
            push_str(var, input->data[i]);
            if (var->info == DBL || var->info == CMP) {
                if (var->info != CMP && input->data[i] == 'j') {
                    var->info = CMP;
                    continue;
                }
                else
                    printf("syntax!\n");
            }

            var->info = VAR;
            for (int j = 0; j < sizeof(BUILT) / sizeof(STR); ++j)
                if (compare_str(BUILT[j], var))
                    var->info = FUN;
        }
    }

    if (var->len)
        add_node_array(nodes_array, create_node(var, sign));

    return nodes_array;
}

NODES_ARRAY* notation_token(NODES_ARRAY* token) {
    STACK* stack = init_stack();
    NODES_ARRAY* notation = init_nodes_array();

    for (int i = 0; i < token->length; ++i) {
        if (take_el(token, i)->info == OPN || take_el(token, i)->info == FUN) {
            if (take_el(token, i)->data[0] == '(' || take_el(token, i)->info == FUN)
                stack = add_to_stack(stack, &token->array[i]);
            else if (take_el(token, i)->data[0] == ')') {
                while (stack->pointer && take_head_stack(stack)->value->data[0] != '(')
                    add_node_array(notation, pop_from_stack(stack));

                pop_from_stack(stack);
                if (stack->pointer)
                    if (take_head_stack(stack)->value->info == FUN)
                        add_node_array(notation, pop_from_stack(stack));
            }
            else {
                int current_priority = get_priority(take_el(token, i));
                while (stack->pointer && current_priority <= get_priority(take_head_stack(stack)->value))
                    add_node_array(notation, pop_from_stack(stack));
                stack = add_to_stack(stack, &token->array[i]);
            }
        }
        else {
            add_node_array(notation, &token->array[i]);
        }
    }
    while (stack->pointer)
        add_node_array(notation, pop_from_stack(stack));

    return notation;
}
