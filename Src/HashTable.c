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
 * File: HashTable.c
 * Description:
 *  This file contains the implementation of the hashtable functions. It includes 
 *  functions to initialize, destroy, insert, get, remove, resize and check if 
 *  hashtable contains key.
 * 
 * Author: BitCode32
 * -----------------------------------------------------------------------------
 */
#include "../Include/Fledasty/HashTable.h"

#include <Hallocy/Allocator.h>

void fledasty_hash_table_initialize(fledasty_hash_table *new_hash_table, size_t (*hash_key_function)(void *key)) {
    new_hash_table->size = 0;
    new_hash_table->capacity = 100;
    new_hash_table->table = (fledasty_hash_table_node**)hallocy_calloc(new_hash_table->capacity, sizeof(fledasty_hash_table_node*));

    new_hash_table->hash_key = hash_key_function;
}

void fledasty_hash_table_destroy(fledasty_hash_table *current_hash_table) {
    for (unsigned int i = 0; i < current_hash_table->capacity; i++) {
        if (current_hash_table->table[i] != NULL) {
            fledasty_hash_table_node *current_hash_table_node = current_hash_table->table[i];
            while (current_hash_table_node != NULL) {
                fledasty_hash_table_node *copy_hash_table_node = current_hash_table_node;
                current_hash_table_node = current_hash_table_node->next;

                hallocy_free(copy_hash_table_node->value);
                hallocy_free(copy_hash_table_node->key);
                hallocy_free(copy_hash_table_node);
            }
        }
    }

    current_hash_table->capacity = 0;
    current_hash_table->size = 0;
}

void fledasty_hash_table_insert(fledasty_hash_table *current_hash_table, void *key, size_t key_size, void *value, size_t value_size) {
    if (current_hash_table->size > (current_hash_table->capacity * 0.75f)) {
        fledasty_hash_table_resize(current_hash_table, current_hash_table->capacity * 2);
    }

    size_t hash = current_hash_table->hash_key(key) % current_hash_table->capacity;
    fledasty_hash_table_node *new_hash_table_node = (fledasty_hash_table_node*)hallocy_malloc(sizeof(fledasty_hash_table_node));

    new_hash_table_node->key_size = key_size;
    new_hash_table_node->key = hallocy_malloc(key_size);
    hallocy_copy_memory(new_hash_table_node->key, key, key_size);

    new_hash_table_node->value = hallocy_malloc(value_size);
    hallocy_copy_memory(new_hash_table_node->value, value, value_size);
    
    new_hash_table_node->next = current_hash_table->table[hash];
    current_hash_table->table[hash] = new_hash_table_node;

    current_hash_table->size++;
}

void *fledasty_hash_table_get(const fledasty_hash_table *current_hash_table, void *key, size_t key_size) {
    size_t hash = current_hash_table->hash_key(key) % current_hash_table->capacity;
    fledasty_hash_table_node *current_hash_table_node = current_hash_table->table[hash];
    while (current_hash_table_node != NULL) {
        if (current_hash_table_node->key_size == key_size && hallocy_compare_memory(current_hash_table_node->key, key, key_size)) {
            return current_hash_table_node->value;
        }

        current_hash_table_node = current_hash_table_node->next;
    }

    return NULL;
}
void fledasty_hash_table_remove(fledasty_hash_table *current_hash_table, void *key, size_t key_size) {
    size_t hash = current_hash_table->hash_key(key) % current_hash_table->capacity;

    fledasty_hash_table_node *previous_hash_table_node = NULL;
    fledasty_hash_table_node *current_hash_table_node = current_hash_table->table[hash];
    while (current_hash_table_node != NULL) {
        if (current_hash_table_node->key_size == key_size && hallocy_compare_memory(current_hash_table_node->key, key, key_size)) {
            if (previous_hash_table_node == NULL) {
                current_hash_table->table[hash] = current_hash_table_node->next;
            } else {
                previous_hash_table_node->next = current_hash_table_node->next;
            }

            current_hash_table->size--;

            hallocy_free(current_hash_table_node->key);
            hallocy_free(current_hash_table_node->value);
            hallocy_free(current_hash_table_node);

            current_hash_table_node = NULL;
        } else {
            previous_hash_table_node = current_hash_table_node;
            current_hash_table_node = current_hash_table_node->next;
        }
    }
}

void fledasty_hash_table_resize(fledasty_hash_table *current_hash_table, size_t new_capacity) {
    fledasty_hash_table_node **new_table = (fledasty_hash_table_node**)hallocy_calloc(new_capacity, sizeof(fledasty_hash_table_node*));

    for (size_t i = 0; i < current_hash_table->capacity; i++) {
        fledasty_hash_table_node *current_hash_table_node = current_hash_table->table[i];
        while (current_hash_table_node != NULL) {
            fledasty_hash_table_node *copy_hash_table_node = current_hash_table_node;
            current_hash_table_node = current_hash_table_node->next;
            
            size_t new_hash = current_hash_table->hash_key(copy_hash_table_node->key) % new_capacity;
            copy_hash_table_node->next = new_table[new_hash];
            new_table[new_hash] = copy_hash_table_node;
        }
    }

    hallocy_free(current_hash_table->table);
    current_hash_table->table = new_table;
    current_hash_table->capacity = new_capacity;
}

bool fledasty_hash_table_has_key(const fledasty_hash_table *current_hash_table, void *key, size_t key_size) {
    size_t hash = current_hash_table->hash_key(key) % current_hash_table->capacity;
    fledasty_hash_table_node *current_hash_table_node = current_hash_table->table[hash];
    while(current_hash_table_node != NULL) {
        if (current_hash_table_node->key_size == key_size && hallocy_compare_memory(current_hash_table_node->key, key, key_size)) {
            return true;
        }

        current_hash_table_node = current_hash_table_node->next;
    }

    return false;
}