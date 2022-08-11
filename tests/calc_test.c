#include <stdio.h>
#include "libs/str.h"
#include "libs/node.h"
#include "libs/parsing.h"

typedef struct unit {
    COMPLEX result;
    char* expression;
    int size;
} UNITTEST;


COMPLEX get_calc(STR* tmp) {
    return calc(notation_token(tokenization_string(tmp)));
}

int main() {
    UNITTEST tests[] = {
            {CMPLXL(11, 0), "10 + 1", 6},
            {CMPLXL(12, 0), "11 + 1", 6}
    };

    for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i) {
        STR* expression = init_str();
        for (int j = 0; j < tests[i].size; ++j)
            push_str(expression, tests[i].expression[j]);

        COMPLEX result = get_calc(expression);
        if (result == tests[i].result)
            printf("TEST CASE %d. OK\n", i);
        else
            printf("TEST CASE %d. WRONG!\n", i);

        delete_str(expression);
    }

    return 0;
}