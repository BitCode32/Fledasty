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
 * File: Queue.h
 * Description:
 *  This file contains the queue data structure and functions. It includes functions 
 *  to initialize, destroy, push, pop, peek and check if queue is empty.
 * 
 * Author: BitCode32
 * -----------------------------------------------------------------------------
 */
#ifndef FLEDASTY_QUEUE
#define FLEDASTY_QUEUE

#include <stddef.h>
#include <stdbool.h>

typedef struct fledasty_queue_node {
    void *value;
    struct fledasty_queue_node *previous, *next;
} fledasty_queue_node;

typedef struct {
    size_t size;
    fledasty_queue_node *start, *end;
} fledasty_queue;

void fledasty_queue_initialize(fledasty_queue *new_queue);
void fledasty_queue_destroy(fledasty_queue *current_queue);

void fledasty_queue_push(fledasty_queue *current_queue, void *value, size_t size);
void *fledasty_queue_pop(fledasty_queue *current_queue);
static inline void *fledasty_queue_peek(const fledasty_queue *current_queue) { return (current_queue->end != NULL) ? current_queue->end->value : NULL; }

static inline bool fledasty_queue_is_empty(const fledasty_queue *current_queue) { return current_queue->size == 0; }

#endif