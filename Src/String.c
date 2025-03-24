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
 * File: String.c
 * Description:
 *  This file contains the implementation of the queue functions. It includes 
 *  functions to initialize, destroy, push, pop and peek.
 * 
 * Author: BitCode32
 * -----------------------------------------------------------------------------
 */
#include "../Include/Fledasty/String.h"

#include <Hallocy/Allocator.h>

void fledasty_string_initialize(fledasty_string *new_string, char *character_string) {
    if (character_string != NULL) {
        size_t character_string_size = 0;
        while (character_string[character_string_size] != '\0') {
            character_string_size++;
        }

        new_string->capacity = character_string_size;
        new_string->size = character_string_size;
        new_string->character_string = (char*)hallocy_malloc(character_string_size);
        
        for (size_t i = 0; i < new_string->size; i++) {
            new_string->character_string[i] = character_string[i];
        }
    } else {
        new_string->size = 0;
        new_string->capacity = 10;
        new_string->character_string = (char*)hallocy_malloc(new_string->capacity);
    }
}

void fledasty_string_destroy(fledasty_string *current_string) {
    if (current_string->capacity > 0) {
      	hallocy_free(current_string->character_string);
    }
}

void fledasty_string_append(fledasty_string *current_string, const char *character_string, const size_t size) {
    if (current_string->capacity <= current_string->size + size) {
        current_string->capacity += size + 1;
        current_string->character_string = (char*)hallocy_realloc(current_string->character_string, current_string->capacity);
    }

    hallocy_copy_memory(current_string->character_string + current_string->size, character_string, size);
    current_string->size += size;

    current_string->character_string[current_string->size] = '\0';
}

void fledasty_string_insert(fledasty_string *current_string, const size_t index, const char *character_string, const size_t size) {
    if (index > current_string->size) {
        return;
    }

    if (current_string->capacity <= current_string->size + size) { 
        current_string->capacity += size + 1;
        current_string->character_string = (char*)hallocy_realloc(current_string->character_string, current_string->capacity);
    }

    hallocy_move_memory(current_string->character_string + (index + size - 1), current_string->character_string + (index - 1), current_string->size - index);
    hallocy_copy_memory(current_string->character_string + index, character_string, size);

    current_string->size += size;
    current_string->character_string[current_string->size] = '\0';
}

void fledasty_string_replace(fledasty_string *current_string, const char *character_string_to_replace, const size_t to_replace_size, const char *character_string_replacement, const size_t replacement_size) {
    size_t max_index = current_string->size - to_replace_size;
    size_t start_index = 0;
    while (start_index < max_index && !hallocy_compare_memory(current_string->character_string + start_index, character_string_to_replace, to_replace_size)) {
        start_index++;
    }

    size_t size_diffrence = replacement_size - to_replace_size;
    if (current_string->capacity <= current_string->size + size_diffrence) {
        current_string->capacity += size_diffrence + 1;
        current_string->character_string = (char*)hallocy_realloc(current_string->character_string, current_string->capacity);
    }

    hallocy_move_memory(current_string->character_string + (start_index + to_replace_size), current_string->character_string + (start_index + replacement_size), current_string->size - (start_index + to_replace_size));
    hallocy_copy_memory(current_string->character_string + start_index, character_string_replacement, replacement_size);

    current_string->size += size_diffrence;
    current_string->character_string[current_string->size] = '\0';
}

void fledasty_string_copy(fledasty_string *destination, const fledasty_string *source) {
    if (destination->capacity <= source->size) {
        destination->capacity = source->size + 1;
        destination->character_string = (char*)hallocy_realloc(destination->character_string, destination->capacity);
    }

    destination->size = source->size;
    hallocy_copy_memory(destination->character_string, source->character_string, source->size);
}

void fledasty_string_swap(fledasty_string *current_string, fledasty_string *other_string) {
    char *copy_character_string = other_string->character_string;
    other_string->character_string = current_string->character_string;
    current_string->character_string = copy_character_string;

    size_t copy_size = other_string->size;
    other_string->size = current_string->size;
    current_string->size = copy_size;

    copy_size = other_string->capacity;
    other_string->capacity = current_string->capacity;
    current_string->capacity = copy_size;
}

void fledasty_string_pop(fledasty_string *current_string) {
    current_string->size -= 1;
    current_string->character_string[current_string->size] = '\0';
}

void fledasty_string_remove(fledasty_string *current_string, const char *character_string, const size_t size) {
    size_t max_index = current_string->size - size;
    size_t start_index = 0;
    while (start_index < max_index && !hallocy_compare_memory(current_string->character_string + start_index, character_string, size)) {
        start_index++;
    }

    if (start_index != max_index) {
        hallocy_copy_memory(current_string->character_string + start_index, current_string->character_string + (start_index + size), max_index - start_index);
        current_string->size -= size;
        current_string->character_string[current_string->size] = '\0';
    }
}

void fledatsy_string_remove_range(fledasty_string *current_string, const size_t start_index, const size_t end_index) {
    if (end_index > current_string->size || start_index > end_index) {
        return;
    }

    hallocy_copy_memory(&(current_string->character_string[start_index]), &(current_string->character_string[end_index]), current_string->size - end_index);
    current_string->size -= (end_index - start_index);
    current_string->character_string[current_string->size] = '\0';
}

void fledasty_string_clear(fledasty_string *current_string) {
    current_string->size = 0;
    current_string->character_string[0] = '\0';
}

bool fledasty_string_has_character_string(const fledasty_string *current_string, const char *character_string, const size_t size) {
    size_t max_index = current_string->size - size;
    size_t current_index = 0;
    while (current_index < max_index) {
        if (hallocy_compare_memory(&(current_string->character_string[current_index]), character_string, size)) {
            return true;
        }

        current_index++;
    }

    return false;
}

size_t fledasty_string_character_string_size(const char *character_string) {
    size_t character_string_size = 0;
    while (character_string[character_string_size] != '\0') {
        character_string_size++;
    }

    return character_string_size;
}