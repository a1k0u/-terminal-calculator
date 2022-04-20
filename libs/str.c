#include "parsing.h"
#include "str.h"
#include <stdlib.h>
#include <stdio.h>


STR* init_str() {
    STR* str = (STR*)malloc(sizeof(STR));
    str->data = (char*)malloc(sizeof(char));
    str->info = NON;
    str->len = 0;
    return str;
}

STR* delete_str(STR *str) {
    free(str->data);
    free(str);
    return NULL;
}

void push_str(STR* str, char symbol) {
    str->len += 1;
    str->data = (char*)realloc(str->data, sizeof(char) * str->len);
    str->data[str->len - 1] = symbol;
}

int compare_str(STR* str1, STR* str2) {
    if (str1->len != str2->len)
        return 0;

    for (int i = 0; i < str1->len; ++i)
        if (str1->data[i] != str2->data[i])
            return 0;

    return 1;
}

STR* delete_symbols(STR* str, char symbol) {
    STR* new_str = init_str();
    for (int i = 0; i < str->len; ++i)
        if (str->data[i] != symbol)
            push_str(new_str, str->data[i]);
    str = delete_str(str);
    return new_str;
}

STR* input_str() {
    char chr;
    STR* new_str = init_str();

    chr = getchar();
    while (chr != '\n')
    {
        push_str(new_str, chr);
        chr = getchar();
    }

    return new_str;
}
