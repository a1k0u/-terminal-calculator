#include <stdlib.h>
#include <stdio.h>
#include "string.h"

STR* init_str()
{
	STR* str = NULL;
	str->len = 0;
	str->word = (char*)malloc(sizeof(char) * str->len);
	return str;
}

STR* del_str(STR* str)
{
    free(str->word);
    str->len = 0;
    str = NULL;
    return str;
}

void push_str(STR* str, char letter)
{
	str->len += 1;
	str->word = (char*)realloc(str->word, sizeof(char) * str->len);
	str->word[str->len-1] = letter;
}

STR* strip_str(STR* str)
{
    STR* new_str = init_str();
    for (int i = 0; i < str->len; ++i)
        if (str->word != ' ')
            push_str(new_str, str->word[i]);
    str = del_str(str);
    return new_str;
}

STR* input_str()
{
    STR* new_str = init_str();
    char chr = getchar();
    while (chr != '\n')
    {
        push_str(new_str, chr);
        chr = getchar();
    }

    new_str = strip_str(new_str);
    return new_str;
}
