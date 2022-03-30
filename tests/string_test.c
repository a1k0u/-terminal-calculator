#include "libs/string.h"

int main()
{
    Str* string = init_str();

    string = input_str();
    print_str(string);

    string = strip_str(string);
    print_str(string);

    push_str(string, 'H');
    print_str(string);

    string = del_str(string);

    return 0;
}
