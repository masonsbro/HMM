#include <stdio.h>
#include <stdlib.h>

#include "../hmmlib.h"
#include "unit_test.h"

int main(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    int expected_num_states = 5;
    int expected_num_tokens = 20;
    int expected_distr_total[5] = {100, 100, 100, 100, 100};
    int expected_distr[5][6] = {{0, 50, 40, 0, 10, 0},
                                {0, 0, 0, 95, 5, 0},
                                {0, 10, 0, 0, 80, 10},
                                {0, 5, 0, 0, 85, 10},
                                {0, 25, 25, 0, 0, 50}};
    char* expected_tokens[20] = {"the", "a", "that", "Tom", "John", "Mary",
                                 "Alice", "Jerry", "cat", "dog", "car", "pen",
                                 "bed", "apple", "bit", "ate", "saw", "played",
                                 "hit", "gave"};
    int expected_token_distr_total[5] = {0, 8, 5, 6, 6};
    int expected_token_distr[5][20] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                       {4, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                       {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                                       {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}};

    HMM* hmm = malloc(sizeof(HMM));
    FILE* stream = fopen("test/hmm_1", "r");
    load_HMM(stream, hmm);
    fclose(stream);

    set_test_name(argv[0]);

    assert_int_e(expected_num_states, hmm->num_states);
    assert_int_e(expected_num_tokens, hmm->num_tokens);

    assert_inta_e(expected_distr_total, hmm->state_distribution_total, 5);

    assert_inta_e(expected_distr[0], hmm->state_distribution[0], 6);
    assert_inta_e(expected_distr[1], hmm->state_distribution[1], 6);
    assert_inta_e(expected_distr[2], hmm->state_distribution[2], 6);
    assert_inta_e(expected_distr[3], hmm->state_distribution[3], 6);
    assert_inta_e(expected_distr[4], hmm->state_distribution[4], 6);

    assert_stra_e(expected_tokens, hmm->tokens, 20);

    assert_inta_e(expected_token_distr_total, hmm->token_distribution_total, 5);

    assert_inta_e(expected_token_distr[0], hmm->token_distribution[0], 20);
    assert_inta_e(expected_token_distr[1], hmm->token_distribution[1], 20);
    assert_inta_e(expected_token_distr[2], hmm->token_distribution[2], 20);
    assert_inta_e(expected_token_distr[3], hmm->token_distribution[3], 20);
    assert_inta_e(expected_token_distr[4], hmm->token_distribution[4], 20);

    finish_test();

    return 0;

}