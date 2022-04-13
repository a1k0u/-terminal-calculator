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
typedef enum functions {PLUS, MINUS, MULTIPLICATION, DIVIDE,
                        POWER, SIN, COS, LN, SQRT, EXP, REAL,
                        IMAG, MAG, PHASE} FUNCS;

typedef struct Node {
    int is_number_flag;
    long double image;
    long double real;
    int operation;
} NODE;

typedef struct Nodes {
    NODE** array;
    int length, capacity;
} NODES_ARR;

NODE* create_node(int is_num, long double image, long double real, char operation);
NODES_ARR* add_node_array(NODES_ARR* nodes_arr, NODE* node);
NODES_ARR* delete_nodes_arr(NODES_ARR* nodes_arr);
NODES_ARR* tokenization_string(STR* input);
NODES_ARR* init_nodes_arr();

#endif //TERMINAL_CALCULATOR_NODE_H
