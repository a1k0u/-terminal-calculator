#include "parsing.h"
#include "node.h"
#include <stdlib.h>
#include <stdio.h>

NODE* create_node(STR* var, int sign) {
    NODE *node = (NODE*)malloc(sizeof(NODE));
    node->value = var;
    node->sign = sign;
    return node;
}

NODES_ARRAY* init_nodes_array() {
    NODES_ARRAY* nodes_arr = (NODES_ARRAY*)malloc(sizeof(NODES_ARRAY));
    nodes_arr->array = (NODE*)malloc(sizeof(NODE));
    nodes_arr->capacity = nodes_arr->length = 0;
    return nodes_arr;
}

NODES_ARRAY* delete_nodes_array(NODES_ARRAY* nodes_arr) {
    for (int i = 0; i < nodes_arr->length; ++i) {
        nodes_arr->array[i].value = delete_str(nodes_arr->array[i].value);
        nodes_arr->array[i] = *delete_node(&nodes_arr->array[i]);
    }
    free(nodes_arr->array);
    free(nodes_arr);
    return NULL;
}

void add_node_array(NODES_ARRAY* nodes_arr, NODE* node) {
    if (nodes_arr->length == nodes_arr->capacity) {
        nodes_arr->capacity = nodes_arr->capacity * 2 + 1;
        nodes_arr->array = (NODE*)realloc(
                nodes_arr->array, sizeof(NODE) * nodes_arr->capacity
                );
    }

    nodes_arr->array[nodes_arr->length++] = *node;
}

NODES_ARRAY* insert_node_array(NODES_ARRAY* nodes_arr, NODE* node, int border, int k) {
    NODES_ARRAY* new_arr = init_nodes_array();
    for (int i = 0; i < border - k; ++i)
        add_node_array(new_arr, &nodes_arr->array[i]);
    add_node_array(new_arr, node);
    for (int i = border + 1; i < nodes_arr->length; ++i)
        add_node_array(new_arr, &nodes_arr->array[i]);

//    nodes_arr = delete_nodes_array(nodes_arr);
    return new_arr;
}

NODE* get_last_node(NODES_ARRAY* nodes_arr) {
    return &nodes_arr->array[nodes_arr->length - 1];
}

STR* take_el(NODES_ARRAY* nodes_array, int i) {
    return nodes_array->array[i].value;
}

NODE* delete_node(NODE* node) {
    node->value = delete_str(node->value);
    free(node);
    return NULL;
}
