#include <stdio.h>
#include "libs/str.h"
#include "libs/node.h"
#include "libs/parsing.h"

int main()
{
    printf(">> ");
    STR* input = input_str();
    STR* tmp = init_str();
    copy_str(tmp, input);
    COMPLEX result = calc(notation_token(tokenization_string(tmp)));
    printf("<< ... = %lf + %lfj", creal(result), cimag(result));
    return 0;
}
