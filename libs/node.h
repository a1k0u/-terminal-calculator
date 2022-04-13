#ifndef TERMINAL_CALCULATOR_NODE_H
#define TERMINAL_CALCULATOR_NODE_H

#include "string.h"

STR variable_type[3][5] = {
        {"NUM", 3},
        {"VAR", 3},
        {"NONE", 4}
};

STR operations[5][2] = {
        {"+", 1},
        {"-", 1},
        {"*", 1},
        {"/", 1},
        {"^", 1},
};

typedef enum var_type {NUM, VAR, NONE} TYPE;
typedef enum functions {SIN, COS, LN, SQRT, EXP, REAL, IMAG, MAG, PHASE} FUNCS;

typedef struct node {
    int is_number_flag;
    long double image;
    long double real;
    char operation;
} NODE;

NODE** tokenization_string(STR* input);
NODE** add_node_array(NODE* node);
NODE* create_node;
#endif //TERMINAL_CALCULATOR_NODE_H
