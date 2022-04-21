#ifndef TERMINAL_CALCULATOR_STR_H
#define TERMINAL_CALCULATOR_STR_H

typedef struct Str {
    char* data;
    int info, len;
} STR;

int compare_str(STR* str1, STR* str2);
void push_str(STR* str, char symbol);
void copy_str(STR* str1, STR* str2);
STR* delete_symbols(STR* str, char symbol);
STR *delete_str(STR *str);
STR* input_str();
STR* init_str();
#endif //TERMINAL_CALCULATOR_STR_H