#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct HashEntry {
    int hash;
    char* key;
    void* value;
    struct HashEntry* next;
} HashEntry;

typedef struct HashTable {
    int num_slots;
    int num_entries;
    int max_entries;
    char** keys;
    struct HashEntry** array;
} HashTable;

void ht_init(HashTable* table, int size);
void* ht_get(HashTable* table, char* key);
void ht_set(HashTable* table, char* key, void* value);
void* ht_remove(HashTable* table, char* key);
void ht_remove_int(HashTable* table, char* key);
int ht_get_int(HashTable* table, char* key);
int ht_get_int_or_default(HashTable* table, char* key, int def);
void ht_set_int(HashTable* table, char* key, int value);
int ht_hash_string(char* string);
void ht_destroy(HashTable* table);

#endif