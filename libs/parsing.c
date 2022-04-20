#include "parsing.h"
#include "stack.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

STR BUILT[][2] = {
        {"sin",   FUN},
        {"cos",   FUN},
        {"ln",    FUN},
        {"sqrt",  FUN},
        {"exp",   FUN},
        {"real",  FUN},
        {"imag",  FUN},
        {"mag",   FUN},
        {"phase", FUN},
};

STR CONSTANT[][2] = {
        {"PI",  CST},
        {"e", CST},
        {"j", IMAG_ONE},
};

STR ACTIONS[][2] = {
        {"+", FIRST},
        {"-", FIRST},
        {"*", SECOND},
        {"/", SECOND},
        {"^", THIRD},
        {"(", EMPTY},
        {")", EMPTY},
};


NODES_ARRAY* tokenization_string(STR* input) {
    NODES_ARRAY* nodes_array = init_nodes_array();
    STR* var = init_str();
    int sign = 1;

    input = delete_symbols(input, ' ');
    for (int i = 0; i < strlen(input->data); ++i) {

        for (int j = 0; j < 7; ++j) {
            if (input->data[i] == ACTIONS[j]->data[0]) {
                if (var->info == NON && (!nodes_array->length ||
                    get_last_node(nodes_array)->value->info == OPN)) {

                    if (ACTIONS[j]->data[0] == '-')
                        sign *= -1;
                    else if (ACTIONS[j]->data[0] == '+')
                        sign *= 1;
                    else {} // syntax error

                    var->info = DBL;
                    break;
                }

                if (strlen(var->data) && var->data[0] == '.') {} // syntax error

                if (strlen(var->data))
                    nodes_array = add_node_array(nodes_array, create_node(var, sign));
                var = init_str();
                sign = 1;

                STR* tmp = init_str();
                strcat(tmp->data, ACTIONS[j]->data);
                tmp->info = OPN;
                nodes_array = add_node_array(nodes_array, create_node(tmp, sign));
            }
        }

        if (isdigit(input->data[i]) || input->data[i] == '.') {

            if (var->info == VAR || var->info == FUN) {
                strncat(var->data, &input->data[i], 1);
                var->info = VAR;
                continue;
            }

            strncat(var->data, &input->data[i], 1);
            var->info = DBL;
        }

        if (isalpha(input->data[i])) {
            strncat(var->data, &input->data[i], 1);

            if (var->info == DBL || var->info == CMP) {
                if (input->data[i] == 'j' && var->info != CMP) {
                    var->info = CMP;
                    continue;
                }
                else {} // syntax error
            }

            var->info = NON;

            for (int j = 0; j < sizeof(BUILT) / sizeof(STR); ++j)
                if (strcmp(BUILT[j]->data, var->data))
                    var->info = FUN;

            for (int j = 0; j < sizeof(CONSTANT) / sizeof(STR); ++j)
                if (strcmp(CONSTANT[j]->data, var->data))
                    var->info = CST;

            if (var->info == NON)
                var->info = VAR;

            continue;
        }

        // syntax error
    }

    if (strlen(var->data))
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
