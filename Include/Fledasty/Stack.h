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
 * File: Stack.h
 * Description:
 *  This file contains the stack data structure and functions. It includes functions 
 *  to initialize, destroy, push, pop, peek and check if stack is empty.
 * 
 * Author: BitCode32
 * -----------------------------------------------------------------------------
 */
#ifndef FLEDASTY_STACK
#define FLEDASTY_STACK

#include <stddef.h>
#include <stdbool.h>

typedef struct fledasty_stack_node{
    void *value;
    struct fledasty_stack_node *next;
} fledasty_stack_node;

typedef struct {
    size_t size;
    fledasty_stack_node *start;
} fledasty_stack;

void fledasty_stack_initialize(fledasty_stack *new_stack);
void fledasty_stack_destroy(fledasty_stack *current_stack);

void fledasty_stack_push(fledasty_stack *current_stack, void *value, size_t size);
void *fledasty_stack_pop(fledasty_stack *current_stack);
inline void *fledasty_stack_peek(const fledasty_stack *current_stack) { return (current_stack->start != NULL) ? current_stack->start->value : NULL; }

inline bool fledasty_stack_is_empty(const fledasty_stack *current_stack) { return current_stack->size == 0; }

#endif