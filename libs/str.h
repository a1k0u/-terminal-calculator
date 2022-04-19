#pragma once

typedef struct Str {
    char* data;
    long double str_info;
} STR;

STR* delete_symbols(STR* str, char symbol);
STR* delete_str(STR* str);
STR* input_str();
STR* init_str();
