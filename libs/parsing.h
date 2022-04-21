#ifndef TERMINAL_CALCULATOR_PARSING_H
#define TERMINAL_CALCULATOR_PARSING_H

#include "str.h"
#include "node.h"
#include <math.h>

enum type {NON, CMP, DBL, OPN, VAR, FUN};
enum priority {FIRST, SECOND, THIRD, EMPTY = -1};


NODES_ARRAY* tokenization_string(STR* input);
NODES_ARRAY* notation_token(NODES_ARRAY* token);
#endif //TERMINAL_CALCULATOR_PARSING_H
