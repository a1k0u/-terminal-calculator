#include <stdlib.h>
#include <stdio.h>
#include "string.h"

STR* init_str() {
    STR* str = (STR*)malloc(sizeof(STR));
    str->word = (char*)malloc(sizeof(char));
    str->len = 0;

    return str;
}

STR* del_str(STR* str) {
    free(str->word);
    str->len = 0;
    str = NULL;

    return str;
}

STR* push_char(STR* str, char letter) {
	str->len += 1;
	str->word = (char*)realloc(
            str->word,
            sizeof(char) * str->len);
	str->word[str->len-1] = letter;

    return str;
}

STR* strip_str(STR* str, char symb) {
    STR* new_str = init_str();

    for (int i = 0; i < str->len; ++i)
        if (str->word[i] != symb)
            push_char(new_str, str->word[i]);

    str = del_str(str);
    return new_str;
}

STR* input_str() {
    char chr;
    STR* new_str = init_str();

    chr = getchar();
    while (chr != '\n')
    {
        new_str = push_char(new_str, chr);
        chr = getchar();
    }

    return new_str;
}

int compare_str(STR* str1, STR* str2) {
    if (str1->len != str2->len)
        return 0;

    for (int i = 0; i < str1->len; ++i)
        if (str1->word[i] != str2->word[i])
            return 0;

    return 1;
}

void print_str(STR* string) {
    printf("%s\n", string->word);
}
