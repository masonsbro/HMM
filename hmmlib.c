#include "hmmlib.h"

#include "hashtable.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGTH 16
#define TOKEN_TABLE_SIZE 10000

void load_HMM(FILE* stream, HMM* hmm) {

    // First, load number of states and number of tokens
    fscanf(stream, " %d %d", &hmm->num_states, &hmm->num_tokens);

    hmm->state_distribution = malloc(hmm->num_states * sizeof(*hmm->state_distribution));
    hmm->state_distribution_total = malloc(hmm->num_states * sizeof(*hmm->state_distribution_total));

    for (int i = 0; i < hmm->num_states; i++) {

        // Each state can transition to any other state as well as to the terminal state (so add 1)
        hmm->state_distribution[i] = malloc((hmm->num_states + 1) * sizeof(int));
        hmm->state_distribution_total[i] = 0;

        for (int j = 0; j < hmm->num_states + 1; j++) {
            // Eat any leading whitespace
            fscanf(stream, " %d", &hmm->state_distribution[i][j]);
            hmm->state_distribution_total[i] += hmm->state_distribution[i][j];
        }

    }

    hmm->tokens = malloc(hmm->num_tokens * sizeof(*hmm->tokens));
    hmm->token_distribution = malloc(hmm->num_states * sizeof(*hmm->token_distribution));
    hmm->token_distribution_total = malloc(hmm->num_states * sizeof(*hmm->token_distribution_total));

    for (int i = 0; i < hmm->num_tokens; i++) {

        // Just allocate a constant amount of space for each token
        hmm->tokens[i] = malloc(MAX_TOKEN_LENGTH * sizeof(*hmm->tokens[i]));

        fscanf(stream, " %s", hmm->tokens[i]);

    }

    for (int i = 0; i < hmm->num_states; i++) {

        hmm->token_distribution[i] = malloc(hmm->num_tokens * sizeof(*hmm->token_distribution[i]));

        hmm->token_distribution_total[i] = 0;

        for (int j = 0; j < hmm->num_tokens; j++) {
            fscanf(stream, " %d", &hmm->token_distribution[i][j]);
            hmm->token_distribution_total[i] += hmm->token_distribution[i][j];
        }

    }

}

void save_HMM(FILE* stream, HMM* hmm) {

    fprintf(stream, "%d %d\n\n", hmm->num_states, hmm->num_tokens);

    for (int i = 0; i < hmm->num_states; i++) {
        for (int j = 0; j < hmm->num_states + 1; j++) {
            fprintf(stream, "%d ", hmm->state_distribution[i][j]);
        }
        fprintf(stream, "\n");
    }

    fprintf(stream, "\n");

    for (int i = 0; i < hmm->num_tokens; i++) {
        fprintf(stream, "%s\n", hmm->tokens[i]);
    }

    fprintf(stream, "\n");

    for (int i = 0; i < hmm->num_states; i++) {
        for (int j = 0; j < hmm->num_tokens; j++) {
            fprintf(stream, "%d ", hmm->token_distribution[i][j]);
        }
        fprintf(stream, "\n");
    }

}

static int choose_random(int* array, int total) {

    int accumulator = 0;
    int threshold = rand() % total + 1;

    for (int i = 0; ; i++) {
        accumulator += array[i];
        if (accumulator >= threshold) {
            return i;
        }
    }
    return -1;

}

int generate_sequence(HMM* hmm, char** sequence, int max_length) {
    
    int cur_state = 0;
    int j = 0;

    while (j < max_length && cur_state != hmm->num_states) {
        // Only try to add a token for states with tokens
        if (hmm->token_distribution_total[cur_state] > 0) {
            int token = choose_random(hmm->token_distribution[cur_state],
                                      hmm->token_distribution_total[cur_state]);
            sequence[j++] = hmm->tokens[token];
        }
        cur_state = choose_random(hmm->state_distribution[cur_state],
                                  hmm->state_distribution_total[cur_state]);
    }

    return j;

}

void train_supervised(HMM* hmm, char** corpus, int* tags, int length) {

    // Will eventually be max(tags) + 1
    hmm->num_states = 0;

    // Maps token -> index in tokens
    HashTable* table = malloc(sizeof(*table));
    ht_init(table, TOKEN_TABLE_SIZE);

    for (int i = 0; i < length; i++) {

        char* token = corpus[i];
        int tag = tags[i];

        if (tag >= hmm->num_states) {
            hmm->num_states = tag + 1;
        }

        // ht_set();

    }

    ht_destroy(table);
    free(table);

}