/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * -----------------------------------------------------------------------------
 * File: Stack.c
 * Description:
 *  This file contains the implementation of the stack functions. It includes 
 *  functions to initialize, destroy, push, pop and peek.
 * 
 * Author: BitCode32
 * -----------------------------------------------------------------------------
 */
#include "../Include/Fledasty/Stack.h"

#include <Hallocy/Allocator.h>

void fledasty_stack_initialize(fledasty_stack *new_stack) {
    new_stack->size = 0;
    new_stack->start = NULL;
}

void fledasty_stack_destroy(fledasty_stack *current_stack) {
    fledasty_stack_node *current_stack_node = current_stack->start;
    while (current_stack_node != NULL) {
        fledasty_stack_node *copy_stack_node = current_stack_node;
        current_stack_node = current_stack_node->next;

        hallocy_free(copy_stack_node->value);
        hallocy_free(copy_stack_node);
    }

    current_stack->size = 0;
}

void fledasty_stack_push(fledasty_stack *current_stack, void *value, size_t size) {
    fledasty_stack_node *new_stack_node = (fledasty_stack_node*)hallocy_malloc(sizeof(fledasty_stack_node));
    new_stack_node->value = hallocy_malloc(size);
    hallocy_copy_memory(new_stack_node->value, value, size);

    new_stack_node->next = current_stack->start;
    current_stack->start = new_stack_node;
}

void *fledasty_stack_pop(fledasty_stack *current_stack) {
    fledasty_stack_node *start_stack_node = current_stack->start;

    current_stack->start = start_stack_node->next;
    void *value = start_stack_node->value;

    hallocy_free(start_stack_node);
    return value;
}