#ifndef TERMINAL_CALCULATOR_PARSING_H
#define TERMINAL_CALCULATOR_PARSING_H

#include "str.h"
#include "node.h"
#include <math.h>
#include <complex.h>
#define Complex long double complex

enum type {NON, CMP, DBL, OPN, VAR, FUN};
enum priority {FIRST, SECOND, THIRD, EMPTY = -1};
enum FUNCS {SIN, COS, LN, SQRT, EXP, REAL, IMAG, MAG, PHASE};


NODES_ARRAY* tokenization_string(STR* input);
NODES_ARRAY* notation_token(NODES_ARRAY* token);
Complex calc(NODES_ARRAY* notation);
#endif //TERMINAL_CALCULATOR_PARSING_H
