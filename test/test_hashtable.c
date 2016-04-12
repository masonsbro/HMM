#include <stdlib.h>
#include <string.h>

#include "unit_test.h"
#include "../hashtable.h"

int main(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    set_test_name(argv[0]);

    HashTable* table = malloc(sizeof(*table));
    ht_init(table, 10);

    int value1 = 0;
    int value2 = 1;
    int value3 = 2;

    char* key1 = "hi";
    char* key2 = "08/";
    char* key3 = "kh";

    char** keys = malloc(3 * sizeof(*keys));
    keys[0] = key1;
    keys[1] = key2;
    keys[2] = key3;

    ht_set_int(table, key1, value1);
    ht_set_int(table, key2, value1);
    ht_set_int(table, key3, value3);
    ht_set_int(table, key2, value2);

    assert_int_e(value1, ht_get_int(table, key1));
    assert_int_e(value2, ht_get_int(table, key2));
    assert_int_e(value3, ht_get_int(table, key3));
    assert_null(ht_get(table, "he"));
    assert_null(ht_get(table, "ng"));

    assert_stra_e(keys, table->keys, 3);

    ht_remove_int(table, key1);

    assert_int_e(value3, ht_get_int(table, key3));
    assert_null(ht_get(table, key1));

    ht_destroy(table);

    finish_test();

    return 0;

}