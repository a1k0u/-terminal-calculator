#pragma once

typedef struct string
{
    char* word;
    int len;
} Str;

Str* init_str();
Str* del_str(Str* str);
void print_str(Str* string);
void push_str(Str* str, char letter);
Str* strip_str(Str* str);
Str* input_str();
