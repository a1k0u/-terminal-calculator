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

STR CONSTANT[][2] = {
        {"PI",  CST, 2},
        {"e", CST, 1},
        {"j", IMAG_ONE, 1},
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


NODES_ARRAY* tokenization_string(STR* input) {
    NODES_ARRAY* nodes_array = init_nodes_array();
    STR* var = init_str();
    int sign = 1;

    input = delete_symbols(input, ' ');
    for (int i = 0; i < input->len; ++i) {

        for (int j = 0; j < 7; ++j) {
            if (input->data[i] == ACTIONS[j]->data[0]) {
                if (var->info == NON && (!nodes_array->length ||
                    get_last_node(nodes_array)->value->info == OPN)) {

                    if (ACTIONS[j]->data[0] == '-')
                        sign *= -1;
                    else if (ACTIONS[j]->data[0] == '+')
                        sign *= 1;
                    else {} // syntax error
                    break;
                }

                if (var->len && var->data[0] == '.') {} // syntax error

                if (var->len)
                    nodes_array = add_node_array(nodes_array, create_node(var, sign));
                var = init_str();
                sign = 1;

                STR* tmp = init_str();
                push_str(tmp, ACTIONS[j]->data[0]);
                tmp->info = OPN;
                nodes_array = add_node_array(nodes_array, create_node(tmp, sign));
            }
        }

        if (isdigit(input->data[i]) || input->data[i] == '.') {

            if (var->info == VAR || var->info == FUN) {
                push_str(var, input->data[i]);
                var->info = VAR;
                continue;
            }

            push_str(var, input->data[i]);
            var->info = DBL;
        }

        if (isalpha(input->data[i])) {
            push_str(var, input->data[i]);

            if (var->info == DBL || var->info == CMP) {
                if (input->data[i] == 'j' && var->info != CMP) {
                    var->info = CMP;
                    continue;
                }
                else {} // syntax error
            }

            var->info = NON;

            for (int j = 0; j < sizeof(BUILT) / sizeof(STR); ++j)
                if (compare_str(BUILT[j], var))
                    var->info = FUN;

            for (int j = 0; j < sizeof(CONSTANT) / sizeof(STR); ++j)
                if (compare_str(CONSTANT[j], var))
                    var->info = CST;

            if (var->info == NON)
                var->info = VAR;

            continue;
        }

        // syntax error
    }

    if (var->len)
        nodes_array = add_node_array(nodes_array, create_node(var, sign));
    var = init_str();

    for (int i = 0; i < nodes_array->length; ++i) {
        if (nodes_array->array[i].sign > 0) {
            printf("+");
        }
        else {
            printf("-");
        }
       printf("%s(%d) ", nodes_array->array[i].value->data, nodes_array->array[i].value->info);
    }
    printf("\n");

    return nodes_array;
}
