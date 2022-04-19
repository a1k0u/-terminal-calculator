#ifndef TERMINAL_CALCULATOR_PARSING_H
#define TERMINAL_CALCULATOR_PARSING_H

#include "string.h"
#include "node.h"

//STR built_in_funcs[][2] = {
//        {"sin", 3},
//        {"cos", 3},
//        {"ln", 2},
//        {"sqrt", 4},
//        {"exp", 3},
//        {"real", 4},
//        {"imag", 4},
//        {"mag", 3},
//        {"phase", 5},
//};

typedef enum var_type {DOUBLE, COMPLEX, OPERATION, VAR, NONE} TYPE;

NODES_ARR* tokenization_string(STR* input);
long double token_processing(NODES_ARR* tokens);
#endif //TERMINAL_CALCULATOR_PARSING_H
