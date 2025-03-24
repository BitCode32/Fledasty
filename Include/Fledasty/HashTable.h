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
#ifndef FLEDASTY_HASH_TABLE
#define FLEDASTY_HASH_TABLE

#include <stddef.h>
#include <stdbool.h>

typedef struct fledasty_hash_table_node {
    size_t key_size;
    void *key, *value;

    struct fledasty_hash_table_node *next;
} fledasty_hash_table_node;

typedef struct {
    size_t size, capacity;
    fledasty_hash_table_node **table;
    size_t (*hash_key)(void *key);
} fledasty_hash_table;

void fledasty_hash_table_initialize(fledasty_hash_table *new_hash_table, size_t (*hash_key_function)(void *key));
void fledasty_hash_table_destroy(fledasty_hash_table *current_hash_table);

void fledasty_hash_table_insert(fledasty_hash_table *current_hash_table, void *key, size_t key_size, void *value, size_t value_size);
void *fledasty_hash_table_get(const fledasty_hash_table *current_hash_table, void *key, size_t key_size);
void fledasty_hash_table_remove(fledasty_hash_table *current_hash_table, void *key, size_t key_size);

void fledasty_hash_table_resize(fledasty_hash_table *current_hash_table, size_t new_capacity);

bool fledasty_hash_table_has_key(const fledasty_hash_table *current_hash_table, void *key, size_t key_size);
static inline bool fledasty_hash_table_is_empty(const fledasty_hash_table *current_hash_table) { return current_hash_table->size == 0; }

#endif