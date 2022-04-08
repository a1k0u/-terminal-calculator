#ifndef TERMINAL_CALCULATOR_NODE_H
#define TERMINAL_CALCULATOR_NODE_H

typedef enum functions {SIN, COS, LN, SQRT, EXP, REAL, IMAG, MAG, PHASE} FUNCS;

typedef struct node {
    long double real;
    long double image;
    // ...
} NODE;

#endif //TERMINAL_CALCULATOR_NODE_H
