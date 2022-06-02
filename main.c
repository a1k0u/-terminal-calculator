#include <stdio.h>
#include "libs/str.h"
#include "libs/node.h"
#include "libs/parsing.h"

int main()
{
    printf(">> ");
    STR *input = input_str();
    STR end = {"exit", 0, 4};
    do {
        STR *tmp = init_str();
        copy_str(tmp, input);
        COMPLEX result = calc(notation_token(tokenization_string(tmp)));
        printf("<< ... = %lf + %lfj\n", creal(result), cimag(result));
        printf(">> ");
        input = input_str();
    } while (!compare_str(input, &end));
    return 0;
}
