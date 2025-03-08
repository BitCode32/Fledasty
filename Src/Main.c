#include <Hallocy/Allocator.h>
#include <Fledasty/Stack.h>
#include <Fledasty/Queue.h>
#include <Fledasty/HashTable.h>
#include <stdio.h>

size_t hash_string(void *key) {
    size_t hash = 5831;

    char *string_key = (char*)key;
    int character = 0;
    while ((character = *string_key++)) {
        hash = ((hash << 5) + hash) + character;
    }

    return hash;
}

typedef struct {
    char *name;
    char *email;
    unsigned int birth_day, birth_month, birth_year;
} user;

int main() {
    fledasty_hash_table new_table;
    fledasty_hash_table_initialize(&new_table, hash_string);

    user new_user;
    new_user.name = "BitCode32";
    new_user.email = "tristanfranssen@strawhats.nl";
    new_user.birth_day = 8;
    new_user.birth_month = 3;
    new_user.birth_year = 2025;

    fledasty_hash_table_insert(&new_table, new_user.name, 10, &new_user, sizeof(user));

    new_user.name = "BitCode64";
    new_user.email = "BitCode64@strawhats.nl";
    new_user.birth_day = 9;
    new_user.birth_month = 4;
    new_user.birth_year = 2025;

    fledasty_hash_table_insert(&new_table, new_user.name, 10, &new_user, sizeof(user));

    if (!fledasty_hash_table_has_key(&new_table, "BitCode32", 10)) {
        printf("BitCode32 not found!\n");
    }

    if (!fledasty_hash_table_has_key(&new_table, "BitCode64", 10)) {
        printf("BitCode64 not found!\n");
    }

    user *stored_user = (user*)fledasty_hash_table_get(&new_table, "BitCode32", 10);
    printf("name: %s\nemail:%s\nBirthdate: %d/%d/%d\n", stored_user->name, stored_user->email, stored_user->birth_day, stored_user->birth_month, stored_user->birth_year);

    stored_user = (user*)fledasty_hash_table_get(&new_table, "BitCode64", 10);
    printf("\nname: %s\nemail:%s\nBirthdate: %d/%d/%d\n", stored_user->name, stored_user->email, stored_user->birth_day, stored_user->birth_month, stored_user->birth_year);

    fledasty_hash_table_remove(&new_table, "BitCode64", 10);
    if (fledasty_hash_table_has_key(&new_table, "BitCode64", 10)) {
        printf("BitCode64 was not removed!\n");
    }

    stored_user = (user*)fledasty_hash_table_get(&new_table, "BitCode64", 10);
    if (stored_user != NULL) {
        printf("Found non existing user!\n");
    }

    fledasty_hash_table_destroy(&new_table);
    return 0;
}