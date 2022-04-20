#ifndef TERMINAL_CALCULATOR_PARSING_H
#define TERMINAL_CALCULATOR_PARSING_H

#include "str.h"
#include "node.h"
#include <math.h>

#define IMAG_ONE 1

enum type {NON, CMP, DBL, OPN, VAR, FUN, CST};
enum priority {FIRST, SECOND, THIRD, EMPTY};

NODES_ARRAY* tokenization_string(STR* input);
long complex token_processing(NODES_ARRAY* tokens);
#endif //TERMINAL_CALCULATOR_PARSING_H
