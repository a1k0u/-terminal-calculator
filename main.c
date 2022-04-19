#include <stdio.h>
#include "libs/string.h"
#include "libs/node.h"
#include "libs/parsing.h"

int main()
{
    STR* input = input_str();
    NODES_ARR* nodes_arr = tokenization_string(input);
    long double result = token_processing(nodes_arr);
    printf("%Lf", result);
    return 0;
}
