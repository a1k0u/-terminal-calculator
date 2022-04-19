#ifndef TERMINAL_CALCULATOR_PARSING_H
#define TERMINAL_CALCULATOR_PARSING_H

#include "str.h"
#include "node.h"
#include <math.h>

#define IMAG_ONE 1

enum type {NONE, COMPLEX, DOUBLE, OPERATION, VARIABLE, FUNCTION, CONST};
enum priority {FIRST, SECOND, THIRD, EMPTY};

STR BUILT[][2] = {
        {"sin",   FUNCTION},
        {"cos",   FUNCTION},
        {"ln",    FUNCTION},
        {"sqrt",  FUNCTION},
        {"exp",   FUNCTION},
        {"real",  FUNCTION},
        {"imag",  FUNCTION},
        {"mag",   FUNCTION},
        {"phase", FUNCTION},
};

STR CONSTANT[][2] = {
        {"PI",  M_PI},
        {"e", M_E},
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

NODES_ARR* tokenization_string(STR* input);
long complex token_processing(NODES_ARR* tokens);
#endif //TERMINAL_CALCULATOR_PARSING_H
