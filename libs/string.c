#include <stdlib.h>
#include <stdio.h>
#include "string.h"

Str* init_str()
{
    Str* str;
    str = (Str*)malloc(sizeof(Str));
	str->word = (char*)malloc(sizeof(char));
    str->len = 0;
    return str;
}

Str* del_str(Str* str)
{
    free(str->word);
    str->len = 0;
    str = NULL;
    return str;
}

void push_str(Str* str, char letter)
{
	str->len += 1;
	str->word = (char*)realloc(str->word, sizeof(char) * str->len);
	str->word[str->len-1] = letter;
}

Str* strip_str(Str* str)
{
    Str* new_str = init_str();

    for (int i = 0; i < str->len; ++i)
        if (str->word[i] != ' ')
            push_str(new_str, str->word[i]);
    str = del_str(str);
    return new_str;
}

Str* input_str()
{
    char chr;
    Str* new_str = init_str();

    chr = getchar();
    while (chr != '\n')
    {
        push_str(new_str, chr);
        chr = getchar();
    }

    return new_str;
}

void print_str(Str* string)
{
    printf("%s\n", string->word);
}