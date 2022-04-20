#include <stdio.h>
#include "libs/str.h"
#include "libs/node.h"
#include "libs/parsing.h"

int main()
{
    STR* input = input_str();
    NODES_ARRAY * nodes_arr = tokenization_string(input);
    return 0;
}
