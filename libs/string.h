#pragma once

typedef struct Str {
    char* word;
    int len;
} STR;

int compare_str(STR* str1, STR* str2);
STR* push_char(STR* str, char symb);
STR* strip_str(STR* str, char symb);
STR* del_str(STR* str);
STR* input_str();
STR* init_str();
