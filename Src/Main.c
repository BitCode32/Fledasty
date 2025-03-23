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
 * File: Main.c
 * Description:
 *  Testing file for the Fledasty library.
 * 
 * Author: BitCode32
 * -----------------------------------------------------------------------------
 */
#include <Hallocy/Allocator.h>
#include <Fledasty/Stack.h>
#include <Fledasty/Queue.h>
#include <Fledasty/HashTable.h>
#include <Fledasty/String.h>
#include <stdio.h>

int main() {
    fledasty_string my_string;
    fledasty_string_initialize(&my_string, "Test");

    fledasty_string_append(&my_string, "123", 3);
    printf("Append (Test123): %s\n", my_string.character_string);
    fledasty_string_insert(&my_string, 0, "123", 3);
    printf("Insert (123Test123): %s\n", my_string.character_string);
    fledasty_string_remove(&my_string, "123", 3);
    printf("Remove (Test123): %s\n", my_string.character_string);
    fledasty_string_insert(&my_string, 1, "est1", 4);
    printf("Insert (Test1est123): %s\n", my_string.character_string);
    fledatsy_string_remove_range(&my_string, 1, 5);
    printf("Remove (Test123): %s\n", my_string.character_string);
    fledasty_string_insert(&my_string, my_string.size, "8", 1);
    printf("Insert (Test1238): %s\n", my_string.character_string);
    fledasty_string_pop(&my_string);
    printf("Pop (Test123): %s\n", my_string.character_string);

    fledasty_string copy_string;
    fledasty_string_initialize(&copy_string, NULL);
    fledasty_string_append(&copy_string, "123", 3);
    printf("Append empty (123): %s\n", copy_string.character_string);

    fledasty_string_copy(&copy_string, &my_string);
    printf("Copy (Test123): %s\n", copy_string.character_string);
    fledasty_string_replace(&copy_string, "123", 3, "4567", 4);
    printf("Replace (Test4567): %s\n", copy_string.character_string);
    fledasty_string_swap(&my_string, &copy_string);
    printf("Swap (Test4567): %s\n", my_string.character_string);

    fledasty_string_clear(&copy_string);
    if (fledasty_string_is_empty(&copy_string)) {
        printf("Cleared string\n");
    }

    if (fledasty_string_has_character_string(&my_string, "Test", 4)) {
        printf("String contains Test\n");
    }

    fledasty_string_destroy(&copy_string);
    fledasty_string_destroy(&my_string);
    return 0;
}