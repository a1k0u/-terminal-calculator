#ifndef TERMINAL_CALCULATOR_NODE_H
#define TERMINAL_CALCULATOR_NODE_H

#include "string.h"

typedef struct Node {
    int type;
    long double image;
    long double real;
    char action;
} NODE;

typedef struct Nodes {
    NODE* array;
    int length, capacity;
} NODES_ARR;

NODE* create_node(STR* var, int type);
NODES_ARR* add_node_array(NODES_ARR* nodes_arr, NODE* node);
NODES_ARR* insert_node_array(NODES_ARR* nodes_arr, NODE* node, int border);
NODES_ARR* delete_nodes_arr(NODES_ARR* nodes_arr);
NODES_ARR* init_nodes_arr();

#endif //TERMINAL_CALCULATOR_NODE_H
