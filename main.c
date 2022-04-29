#include <stdio.h>
#include "libs/str.h"
#include "libs/node.h"
#include "libs/parsing.h"

int main()
{
    printf(">> ");
    STR* input = input_str();
    Complex result = solve(input);
    printf("%s = %lf + %lfj", input->data, creal(result), cimag(result));
    return 0;
}
