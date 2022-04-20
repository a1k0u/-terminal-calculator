#pragma once

typedef struct Str {
    char* data;
    int info, len;
} STR;

int compare_str(STR* str1, STR* str2);
void push_str(STR* str, char symbol);
STR* delete_symbols(STR* str, char symbol);
STR *delete_str(STR *str);
STR* input_str();
STR* init_str();
