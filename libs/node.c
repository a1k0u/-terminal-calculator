#include "node.h"
#include "parsing.h"
#include <stdlib.h>

NODE* create_node(STR* var, int type) {
    long double image = 0, real = 0;

    if (type == COMPLEX) {
        var = strip_str(var, 'j');
        image = atof(var->word);
    }
    else if (type == DOUBLE)
        real = atof(var->word);

    NODE *node = (NODE*)malloc(sizeof(NODE));
    node->type = type;
    node->image = image;
    node->real = real;
    node->operation = var->word[0];

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

NODES_ARR* insert_node_array(NODES_ARR* nodes_arr, NODE* node, int border) {
    NODES_ARR* new_arr = init_nodes_arr();
    for (int i = 0; i < border - 2; ++i)
        new_arr = add_node_array(new_arr, nodes_arr->array[i]);
    new_arr = add_node_array(new_arr, node);
    for (int i = border + 1; i < nodes_arr->length; ++i)
        new_arr = add_node_array(new_arr, nodes_arr->array[i]);

    nodes_arr = delete_nodes_arr(nodes_arr);
    return new_arr;
}
