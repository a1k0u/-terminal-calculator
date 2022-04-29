#ifndef TERMINAL_CALCULATOR_PARSING_H
#define TERMINAL_CALCULATOR_PARSING_H

#include "str.h"
#include "node.h"
#include <math.h>
#include <complex.h>
#define COMPLEX long double complex

enum type {NON, CMP, DBL, OPN, VAR, FUN};
enum priority {FIRST, SECOND, THIRD, EMPTY = -1};
enum functions {SIN, COS, LN, SQRT, EXP, REAL, IMAG, MAG, PHASE};
enum operations {PLUS, MINUS, MULTIPLY, DIVIDE, POWER};
enum constants {PI, E, J};
enum insert_flags {RESULT_NONE, RESULT_FUNC, RESULT_ACTION};

NODES_ARRAY* tokenization_string(STR* input);
NODES_ARRAY* notation_token(NODES_ARRAY* token);
COMPLEX calc(NODES_ARRAY* notation);
#endif //TERMINAL_CALCULATOR_PARSING_H
