#include <stdio.h>
#include <stdlib.h>

#include "../hmmlib.h"
#include "unit_test.h"

int main(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    set_test_name(argv[0]);

    HMM* hmm = malloc(sizeof(*hmm));
    hmm->num_states = 3;
    hmm->num_tokens = 2;
    hmm->state_distribution_total = malloc(3 * sizeof(*hmm->state_distribution_total));
    hmm->state_distribution = malloc(3 * sizeof(*hmm->state_distribution));
    hmm->tokens = malloc(2 * sizeof(*hmm->tokens));
    hmm->token_distribution_total = malloc(3 * sizeof(*hmm->token_distribution_total));
    hmm->token_distribution = malloc(3 * sizeof(*hmm->token_distribution));

    hmm->state_distribution_total[0] = 1;
    hmm->state_distribution_total[1] = 1;
    hmm->state_distribution_total[2] = 1;

    hmm->state_distribution[0] = malloc(4 * sizeof(*hmm->state_distribution[0]));
    hmm->state_distribution[0][0] = 0;
    hmm->state_distribution[0][1] = 1;
    hmm->state_distribution[0][2] = 0;
    hmm->state_distribution[0][3] = 0;

    hmm->state_distribution[1] = malloc(4 * sizeof(*hmm->state_distribution[1]));
    hmm->state_distribution[1][0] = 0;
    hmm->state_distribution[1][1] = 0;
    hmm->state_distribution[1][2] = 1;
    hmm->state_distribution[1][3] = 0;

    hmm->state_distribution[2] = malloc(4 * sizeof(*hmm->state_distribution[2]));
    hmm->state_distribution[2][0] = 0;
    hmm->state_distribution[2][1] = 0;
    hmm->state_distribution[2][2] = 0;
    hmm->state_distribution[2][3] = 1;

    hmm->tokens[0] = "a";
    hmm->tokens[1] = "the";

    hmm->token_distribution_total[0] = 0;
    hmm->token_distribution_total[1] = 1;
    hmm->token_distribution_total[2] = 1;

    hmm->token_distribution[0] = malloc(2 * sizeof(*hmm->token_distribution[0]));
    hmm->token_distribution[0][0] = 0;
    hmm->token_distribution[0][1] = 0;

    hmm->token_distribution[1] = malloc(2 * sizeof(*hmm->token_distribution[1]));
    hmm->token_distribution[1][0] = 1;
    hmm->token_distribution[1][1] = 0;

    hmm->token_distribution[2] = malloc(2 * sizeof(*hmm->token_distribution[2]));
    hmm->token_distribution[2][0] = 0;
    hmm->token_distribution[2][1] = 1;

    int expected_length = 2;
    char** expected_sequence = malloc(2 * sizeof(*expected_sequence));
    expected_sequence[0] = "a";
    expected_sequence[1] = "the";

    char** actual_sequence = malloc(5 * sizeof(*actual_sequence));

    // Test generating full-length (nonbinding max_length)
    assert_int_e(expected_length, generate_sequence(hmm, actual_sequence, 5));
    assert_stra_e(expected_sequence, actual_sequence, expected_length);

    expected_length = 1;
    expected_sequence[0] = "a";
    expected_sequence[1] = NULL;
    actual_sequence[0] = NULL;
    actual_sequence[1] = NULL;

    // Test binding max_length
    assert_int_e(expected_length, generate_sequence(hmm, actual_sequence, 1));
    assert_stra_e(expected_sequence, actual_sequence, expected_length);

    finish_test();

    return 0;

}