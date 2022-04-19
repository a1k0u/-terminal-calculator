#include "parsing.h"
#include "str.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


STR* init_str() {
    STR* str = (STR*)malloc(sizeof(STR));
    str->data = (char*)malloc(sizeof(char));
    str->str_info = NONE;
    return str;
}

STR* delete_str(STR* str) {
    free(str->data);
    free(str);
    return NULL;
}

STR* delete_symbols(STR* str, char symbol) {
    STR* new_str = init_str();
    for (int i = 0; i < strlen(str->data); ++i)
        if (str->data[i] != symbol)
            strncat(new_str->data, &str->data[i], 1);
    str = delete_str(str);
    return new_str;
}

STR* input_str() {
    char chr;
    STR* new_str = init_str();

    chr = getchar();
    while (chr != '\n')
    {
        strncat(new_str->data, &chr, 1);
        chr = getchar();
    }

    return new_str;
}
