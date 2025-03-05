#include <Hallocy/Allocator.h>
#include <stdio.h>

int main() {
    char *my_string = (char*)hallocy_malloc(10);
    hallocy_set_memory(my_string, 'a', 10);

    printf("%s\n", my_string);

    hallocy_free(my_string);
    return 0;
}