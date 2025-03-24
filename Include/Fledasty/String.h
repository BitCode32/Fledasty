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
 * File: String.h
 * Description:
 *  This file contains the string structure and functions. It includes functions 
 *  to initialize, destroy, append, insert, replace, copy, swap, pop, remove, 
 *  remove range, check if string contains character and calculate string size.
 * 
 * Author: BitCode32
 * -----------------------------------------------------------------------------
 */
#ifndef FLEDASTY_STRING
#define FLEDASTY_STRING

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    size_t size, capacity;
    char *character_string;
} fledasty_string;

void fledasty_string_initialize(fledasty_string *new_string, char *character_string);
void fledasty_string_destroy(fledasty_string *current_string);

void fledasty_string_append(fledasty_string *current_string, const char *character_string, const size_t size);
void fledasty_string_insert(fledasty_string *current_string, const size_t index, const char *character_string, const size_t size);

void fledasty_string_replace(fledasty_string *current_string, const char *character_string_to_replace, const size_t to_replace_size, const char *character_string_replacement, const size_t replacement_size);

void fledasty_string_copy(fledasty_string *destination, const fledasty_string *source);
void fledasty_string_swap(fledasty_string *current_string, fledasty_string *other_string);

void fledasty_string_pop(fledasty_string *current_string);
void fledasty_string_remove(fledasty_string *current_string, const char *character_string, const size_t size);
void fledatsy_string_remove_range(fledasty_string *current_string, const size_t start_index, const size_t end_index);
void fledasty_string_clear(fledasty_string *current_string);

bool fledasty_string_has_character_string(const fledasty_string *current_string, const char *character_string, const size_t size);
static inline bool fledasty_string_is_empty(const fledasty_string *current_string) { return current_string->size == 0; }

size_t fledasty_string_character_string_size(const char *character_string);

#endif