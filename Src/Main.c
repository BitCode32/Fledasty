#include <Hallocy/Allocator.h>
#include <Fledasty/Stack.h>
#include <stdio.h>

int main() {
    fledasty_stack test_stack;
    fledasty_stack_initialize(&test_stack);

    for (unsigned int i = 5; i < 10; i++) {
        fledasty_stack_push(&test_stack, &i, sizeof(int));
    }

    printf("Peek: %d\n", *((int*)fledasty_stack_peek(&test_stack)));

    for (unsigned int i = 0; i < 5; i++) {
        int *popped_value = (int*)fledasty_stack_pop(&test_stack);
        printf("Popped: %d\n", *popped_value);
        hallocy_free(popped_value);
    }

    fledasty_stack_destroy(&test_stack);
    return 0;
}