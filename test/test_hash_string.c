#include "unit_test.h"
#include "../hashtable.h"

int main(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    set_test_name(argv[0]);

    char string1[] = "hi";
    int expected1 = 'h' + 'i' * 3;

    assert_int_e(expected1, ht_hash_string(string1));

    char string2[] = "08/";
    int expected2 = '0' + '8' * 3 + '/' * 9;

    assert_int_e(expected2, ht_hash_string(string2));

    char string3[] = "kh";
    int expected3 = expected1;

    assert_int_e(expected3, ht_hash_string(string3));

    finish_test();

    return 0;

}