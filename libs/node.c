#include "node.h"
#include "stack.h"

NODE** tokenization_string(STR* input) {
    STACK* stack = init_stack();
    STR* variable = init_str();
    STR* type = variable_type[NONE];

    input = strip_str(input, ' ');
    for (int i = 0; i < input->len; ++i) {
        if ('0' <= input->word[i] && input->word[i]  <= '9' || input->word[i] == '.') {
            if (compare_str(type, variable_type[VAR])) {
                continue;
            }

            type = variable_type[NUM];
            variable = push_char(variable, input->word[i]);
        }

        if ('a' <= input->word[i] && input->word[i] <= 'z' ||
                    'A' <= input->word[i] && input->word[i] <= 'Z') {
            if (compare_str(type, variable_type[NUM])) {}
        }

        if (variable->len == 1)
            for (int j = 0; j < sizeof(operations) / sizeof(STR); ++j)
                if (compare_str(variable, operations[j])) {
                    stack = add_to_stack(stack, variable);

                    variable = del_str(variable);
                    variable = init_str();
                }

    }

    return NULL;
}
