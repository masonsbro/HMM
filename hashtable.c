#include "hashtable.h"

#include <stdlib.h>
#include <string.h>

#define DEFAULT_KEYS_ARRAY_SIZE 8

static int mod(int a, int b) {
    int r = a % b;
    if (r < 0) r += b;
    return r;
}

void ht_init(HashTable* table, int size) {
    table->num_slots = size;
    table->num_entries = 0;
    table->max_entries = DEFAULT_KEYS_ARRAY_SIZE;
    table->keys = malloc(table->max_entries * sizeof(*table->keys));
    table->array = malloc(size * sizeof(*table->array));
}

void* ht_get(HashTable* table, char* key) {
    int hash = ht_hash_string(key);
    int hash_mod = mod(hash, table->num_slots);
    HashEntry* item;
    for (item = table->array[hash_mod];
         item != NULL && strcmp(key, item->key) != 0; item = item->next);
    if (item == NULL) {
        return NULL;
    } else {
        return item->value;
    }
}

void ht_set(HashTable* table, char* key, void* value) {
    int hash = ht_hash_string(key);
    int hash_mod = mod(hash, table->num_slots);
    HashEntry* item;
    HashEntry* prev;
    for (prev = NULL, item = table->array[hash_mod];
         item != NULL && strcmp(key, item->key) != 0; prev = item, item = item->next);
    if (item == NULL) {
        HashEntry* entry = malloc(sizeof(*entry));
        if (prev == NULL) {
            table->array[hash_mod] = entry;
        } else {
            prev->next = entry;
        }
        entry->hash = hash;
        entry->key = malloc((strlen(key) + 1) * sizeof(*entry->key));
        strcpy(entry->key, key);
        entry->value = value;
        entry->next = NULL;
        if (table->num_entries >= table->max_entries) {
            table->max_entries *= 2;
            table->keys = realloc(table->keys, table->max_entries);
        }
        table->keys[table->num_entries++] = entry->key;
    } else {
        item->hash = hash;
        item->value = value;
    }
}

/* Will not remove from keys array */
void* ht_remove(HashTable* table, char* key) {
    int hash = ht_hash_string(key);
    int hash_mod = mod(hash, table->num_slots);
    HashEntry* item;
    HashEntry* prev;
    for (prev = NULL, item = table->array[hash_mod];
         item != NULL && strcmp(key, item->key) != 0; prev = item, item = item->next);
    if (item != NULL) {
        if (prev == NULL) {
            table->array[hash_mod] = NULL;
        } else {
            prev->next = item->next;
        }
        void* value = item->value;
        free(item);
        return value;
    }
    return NULL;
}

/* Removes AND frees the int */
void ht_remove_int(HashTable* table, char* key) {
    void* value = ht_remove(table, key);
    if (value != NULL) {
        free(value);
    }
}

int ht_get_int(HashTable* table, char* key) {
    return *((int*) ht_get(table, key));
}

int ht_get_int_or_default(HashTable* table, char* key, int def) {

    void* value = ht_get(table, key);

    if (value == NULL) {
        return def;
    } else {
        return *((int*) value);
    }
    
}

void ht_set_int(HashTable* table, char* key, int value) {
    int* real_value = malloc(sizeof(*real_value));
    *real_value = value;
    ht_set(table, key, real_value);
}

int ht_hash_string(char* string) {
    int sum = 0;
    for (int i = 0, mul = 1; string[i] != 0; i++, mul *= 3) {
        sum += mul * string[i];
    }
    return sum;
}

void ht_destroy(HashTable* table) {
    for (int i = 0; i < table->num_entries; i++) {
        char* key = table->keys[i];
        ht_remove(table, key);
        free(key);
    }

}