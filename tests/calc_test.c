#include <stdio.h>
#include "libs/str.h"
#include "libs/node.h"
#include "libs/parsing.h"

typedef struct unit {
    COMPLEX result;
    char* expression;
} UNITTEST;


COMPLEX get_calc(STR* tmp) {
    return calc(notation_token(tokenization_string(tmp)));
}

int main() {
    UNITTEST tests[] = {
            {CMPLXL(11, 0), "10 + 1"},
            {CMPLXL(12, 0), "11 + 1"}
    };

    printf("%s = %lf + %lfj\n",
           tests[0].expression,
           creal(tests[0].result),
           cimag(tests[0].result)
           );

    return 0;
}