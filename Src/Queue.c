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
 * File: Queue.c
 * Description:
 *  This file contains the implementation of the queue functions. It includes 
 *  functions to initialize, destroy, push, pop and peek.
 * 
 * Author: BitCode32
 * -----------------------------------------------------------------------------
 */
#include "../Include/Fledasty/Queue.h"

#include <Hallocy/Allocator.h>

void fledasty_queue_initialize(fledasty_queue *new_queue) {
    new_queue->size = 0;
    new_queue->start = NULL;
    new_queue->end = NULL;
}

void fledasty_queue_destroy(fledasty_queue *current_queue) {
    fledasty_queue_node *current_queue_node = current_queue->start;
    while (current_queue_node != NULL) {
        fledasty_queue_node *copy_queue_node = current_queue_node;
        current_queue_node = current_queue_node->next;

        hallocy_free(copy_queue_node->value);
        hallocy_free(copy_queue_node);
    }

    current_queue->size = 0;
}

void fledasty_queue_push(fledasty_queue *current_queue, void *value, size_t size) {
    fledasty_queue_node *new_queue_node = (fledasty_queue_node*)hallocy_malloc(sizeof(fledasty_queue_node));
    new_queue_node->value = hallocy_malloc(size);
    hallocy_copy_memory(new_queue_node->value, value, size);

    new_queue_node->previous = NULL;
    new_queue_node->next = current_queue->start;

    if (current_queue->start == NULL) {
        current_queue->end = new_queue_node;
    } else {
        current_queue->start->previous = new_queue_node;
    }

    current_queue->start = new_queue_node;
}

void *fledasty_queue_pop(fledasty_queue *current_queue) {
    fledasty_queue_node *end_queue_node = current_queue->end;

    if (end_queue_node->previous == NULL) {
        current_queue->start = NULL;
        current_queue->end = NULL;
    } else {
        current_queue->end = end_queue_node->previous;
        current_queue->end->next = NULL;
    }

    void *value = end_queue_node->value;
    hallocy_free(end_queue_node);
    return value;
}