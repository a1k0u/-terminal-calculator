#include "parsing.h"
#include "stack.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "hash_table.h"
#include <complex.h>


Complex hash_table[1000000] = {0};
int keys[1000000] = {0};

long int M = 1000000;
long int p = 127;

int hash(STR* data) {
    long int index = 0, k = 1;
    for (int i = 0; i < data->len; ++i) {
        index += (long int) data->data[i] * k;
        index %= M;
        k *= p;
    }

    return index % M;
}

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

STR CONSTANTS[][3] = {
        {"PI", VAR, 3},
        {"e", VAR, 1},
        {"j", VAR, 1},
};

int get_priority(STR* operation) {
    for (int i = 0; i < 7; ++i)
        if (compare_str(operation, ACTIONS[i]))
            return ACTIONS[i]->info;
}

Complex calc(NODES_ARRAY* notation) {
    int index = 0;
    while (notation->length != 1) {
        if (!index) {
            for (int i = 0; i < notation->length; ++i) {
                if (notation->array[i].value->info != OPN && notation->array[i].value->info != FUN) {
                    printf("%.3lf+%.3lfj ", creal(notation->array[i].number), cimag(notation->array[i].number));
                }
                else {
                    printf("%s ", notation->array[i].value->data);
                }
            }
            printf("\n");
        }
        if(notation->array[index].value->info == OPN) {
            Complex a = notation->array[index - 2].number;
            Complex b = notation->array[index - 1].number;
            Complex result;
            if (notation->array[index].value->data[0] == '+')
                result = a + b;
            else if (notation->array[index].value->data[0] == '-')
                result = a - b;
            else if (notation->array[index].value->data[0] == '*')
                result = a * b;
            else if (notation->array[index].value->data[0] == '/')
                result = a / b;
            else if (notation->array[index].value->data[0] == '^')
                result = cpowl(a, b);

            STR tmp = {"", CMP, 0};
            NODE* new_node = create_node(&tmp, 1);
            new_node->number = result;
            notation = insert_node_array(notation, new_node, index, 2);
            index = 0;
            continue;
        }
        else if (notation->array[index].value->info == FUN) {
            Complex a = notation->array[index - 1].number;
            Complex result;
            STR* ptr = notation->array[index].value;
            if (compare_str(ptr, BUILT[SIN]))
                result = csinl(a);
            else if (compare_str(ptr, BUILT[COS]))
                result = ccosl(a);
            else if (compare_str(ptr, BUILT[LN]))
                result = clogl(a);
            else if (compare_str(ptr, BUILT[SQRT]))
                result = csqrtl(a);
            else if (compare_str(ptr, BUILT[EXP]))
                result = cexpl(a);
            else if (compare_str(ptr, BUILT[REAL]))
                result = CMPLXL(creal(a), 0);
            else if (compare_str(ptr, BUILT[IMAG]))
                result = CMPLXL(cimag(a), 0);
/*            else if (compare_str(ptr, BUILT[MAG]))
                result =
            else if (compare_str(ptr, BUILT[PHASE]))
                result = CMPLXL(0, cimag(a));
*/
            STR tmp = {"", CMP, 0};
            NODE* new_node = create_node(&tmp, 1);
            new_node->number = result;
            notation = insert_node_array(notation, new_node, index, 1);
            index = 0;
            continue;
        }
        index += 1;
    }

    return notation->array[0].number;
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
                    get_last_node(nodes_array)->value->info == OPN &&
                        get_last_node(nodes_array)->value->data[0] != ')')) {

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


    for (int i = 0; i < nodes_array->length; ++i) {
        if (nodes_array->array[i].value->info != OPN) {
            if (nodes_array->array[i].sign < 0) {
                printf("-");
            }
        }
        printf("%s(%s) ", nodes_array->array[i].value->data,
               nodes_array->array[i].value->info == FUN ? "FUN" :
               nodes_array->array[i].value->info == VAR ? "VAR" :
               nodes_array->array[i].value->info == CMP ? "CMP" :
               nodes_array->array[i].value->info == DBL ? "DBL" :
               "OPN");
    }
    printf("\n");

    return nodes_array;
}

NODES_ARRAY* notation_token(NODES_ARRAY* token) {
    keys[hash(CONSTANTS[0])] = 1;
    keys[hash(CONSTANTS[1])] = 1;
    keys[hash(CONSTANTS[2])] = 1;

    hash_table[hash(CONSTANTS[0])] = CMPLXL(M_PI, 0);
    hash_table[hash(CONSTANTS[1])] = CMPLXL(M_E, 0);
    hash_table[hash(CONSTANTS[2])] = CMPLXL(0, 1);

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
            if (token->array[i].value->info == VAR) {
                long int index_of_hash_table = hash(token->array[i].value);
                if (!keys[index_of_hash_table]) {
                    printf("%s? >> ", token->array[i].value->data);
                    STR* expression = input_str();
                    Complex value = calc(notation_token(tokenization_string(expression)));
                    hash_table[index_of_hash_table] = value;
                    printf("%s = %lf + %lfj\n", token->array[i].value->data, creal(value), cimag(value));
                }
                keys[index_of_hash_table] = 1;

                token->array[i].number = token->array[i].sign * hash_table[index_of_hash_table];
            }
            else if (token->array[i].value->info == DBL) {
                token->array[i].number = CMPLXL(token->array[i].sign * atof(token->array[i].value->data), 0);
            }
            else if (token->array[i].value->info == CMP) {
                token->array[i].value = delete_symbols(token->array[i].value, 'j');
                token->array[i].number = CMPLXL(0, token->array[i].sign * atof(token->array[i].value->data));
            }
            add_node_array(notation, &token->array[i]);
        }
    }
    while (stack->pointer)
        add_node_array(notation, pop_from_stack(stack));

    return notation;
}