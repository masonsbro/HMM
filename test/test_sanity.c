#include <stdio.h>
#include <stdlib.h>

#include "../hmmlib.h"
#include "unit_test.h"

int main(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    set_test_name("test_sanity");

    // First, load the file (this is correct as per test_load)
    HMM* hmm = malloc(sizeof(HMM));
    FILE* stream_1 = fopen("test/hmm_1", "r");
    load_HMM(stream_1, hmm);
    fseek(stream_1, 0, SEEK_END);
    int length_1 = ftell(stream_1);
    fseek(stream_1, 0, SEEK_SET);
    char* string_1 = malloc((length_1 + 1) * sizeof(*string_1));
    fread(string_1, length_1, 1, stream_1);
    fclose(stream_1);
    string_1[length_1] = 0;

    FILE* stream_2 = fopen("test/hmm_1_dup", "w");
    save_HMM(stream_2, hmm);
    fclose(stream_2);

    FILE* stream_3 = fopen("test/hmm_1_dup", "r");
    fseek(stream_3, 0, SEEK_END);
    int length_2 = ftell(stream_3);
    fseek(stream_3, 0, SEEK_SET);
    char* string_2 = malloc((length_2 + 1) * sizeof(*string_2));
    fread(string_2, length_2, 1, stream_3);
    fclose(stream_3);
    string_2[length_2] = 0;

    remove("test/hmm_1_dup");

    assert_str_e(string_1, string_2);

    finish_test();

    return 0;

}