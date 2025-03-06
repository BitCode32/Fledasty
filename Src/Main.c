#include <Hallocy/Allocator.h>
#include <Fledasty/Stack.h>
#include <Fledasty/Queue.h>
#include <stdio.h>

int main() {
    fledasty_queue test_queue;
    fledasty_queue_initialize(&test_queue);

    for (unsigned int i = 5; i < 10; i++) {
        fledasty_queue_push(&test_queue, &i, sizeof(int));
    }

    printf("Peek: %d\n", *((int*)fledasty_queue_peek(&test_queue)));

    for (unsigned int i = 0; i < 5; i++) {
        int *popped_value = (int*)fledasty_queue_pop(&test_queue);
        printf("Popped: %d\n", *popped_value);
        hallocy_free(popped_value);
    }

    fledasty_queue_destroy(&test_queue);
    return 0;
}